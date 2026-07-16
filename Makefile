# ======================================
# Top-level Makefile for cpp-coding-exercise
# ======================================

# Auto-detect all subdirectories that contain a Makefile
SUBDIRS := $(dir $(wildcard */Makefile))

# Default sanitizer (can be overridden)
SANITIZE ?= address
COVERAGE_MIN ?= 80
COVERAGE_FUNCTION_MIN ?= 80
COVERAGE_BRANCH_MIN ?= 70
COVERAGE_DIR ?= coverage
GCOV ?= gcov-14
IS_WSL := $(shell grep -qi microsoft /proc/sys/kernel/osrelease 2>/dev/null && echo 1)

ifeq ($(IS_WSL),1)
DEFAULT_SANITIZERS := address undefined
else
DEFAULT_SANITIZERS := address thread undefined
endif

SANITIZERS ?= $(DEFAULT_SANITIZERS)

.PHONY: all build clean run test format lint coverage check $(SUBDIRS)

# --------------------------
# Build all examples
# --------------------------
all: $(SUBDIRS)

build: all

$(SUBDIRS):
	@echo "=== Building $@ with SANITIZE=$(SANITIZE) ==="
	$(MAKE) -C $@ SANITIZE=$(SANITIZE)

# --------------------------
# Run all examples (optional)
# --------------------------
run:
	@for dir in $(SUBDIRS); do \
		echo "=== Running $$dir ==="; \
		(cd $$dir && $(MAKE) SANITIZE=$(SANITIZE) run) || exit 1; \
		## Run tests if present and fail the test if tests fail \
		if [ -f "$$dir/tests.sh" ]; then \
			echo "=== Running tests in $$dir ==="; \
			(cd $$dir && ./tests.sh) || exit 1; \
		fi; \
	done

test: run

# --------------------------
# Clean all examples
# --------------------------
clean:
	@set -e; for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	@rm -rf $(COVERAGE_DIR)
	@find . -name '*.gcda' -o -name '*.gcno' | xargs -r rm -f

.PHONY: check-format-all check-format

format:
	@find . -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.c' -o -name '*.h' \) \
		-not -path './.git/*' -exec clang-format -i {} +

lint: check-format-all

check-format-all:
	@set -e; for dir in $(SUBDIRS); do \
	    if [ -d "$$dir" ]; then \
	        echo "=== clang-format check in $$dir ==="; \
	        $(MAKE) -f $(MAKEFILE_LIST) check-format DIR=$$dir; \
	    fi; \
	done

check-format:
	@cd $(DIR); \
	echo "Checking clang-format in $(DIR)"; \
	if command -v bash >/dev/null 2>&1; then \
	    bash -c 'shopt -s nullglob; files=( *.cpp *.hpp *.c *.h ); \
	    if [ $${#files[@]} -ne 0 ]; then \
	        clang-format --Werror --dry-run "$${files[@]}"; \
	    else \
	        echo "No source files found, skipping"; \
	    fi'; \
	else \
	    echo "Bash not found; skipping clang-format check"; \
	fi

coverage:
	@$(MAKE) clean
	@$(MAKE) SANITIZE= COVERAGE=1 build
	@$(MAKE) SANITIZE= COVERAGE=1 test
	@mkdir -p $(COVERAGE_DIR)
	@gcovr --root . \
		--gcov-executable $(GCOV) \
		--exclude-unreachable-branches --exclude-throw-branches \
		--txt --html-details $(COVERAGE_DIR)/index.html \
		--xml $(COVERAGE_DIR)/coverage.xml --xml-pretty \
		--json-summary $(COVERAGE_DIR)/summary.json --json-summary-pretty \
		--fail-under-line $(COVERAGE_MIN) \
		--fail-under-function $(COVERAGE_FUNCTION_MIN) \
		--fail-under-branch $(COVERAGE_BRANCH_MIN)

check: lint
	@if [ "$(IS_WSL)" = "1" ] && [ "$(SANITIZERS)" = "$(DEFAULT_SANITIZERS)" ]; then \
		echo "=== Skipping ThreadSanitizer runtime checks on WSL2 ==="; \
	fi
	@set -e; for sanitizer in $(SANITIZERS); do \
		echo "=== Checking with $$sanitizer sanitizer ==="; \
		$(MAKE) clean; \
		$(MAKE) SANITIZE=$$sanitizer build; \
		$(MAKE) SANITIZE=$$sanitizer test; \
	done
	@$(MAKE) clean

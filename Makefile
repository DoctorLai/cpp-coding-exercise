# ======================================
# Top-level Makefile for cpp-coding-exercise
# ======================================

# Auto-detect all subdirectories that contain a Makefile
SUBDIRS := $(dir $(wildcard */Makefile))

# Default sanitizer (can be overridden)
SANITIZE ?= address

.PHONY: all clean run $(SUBDIRS)

# --------------------------
# Build all examples
# --------------------------
all: $(SUBDIRS)

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

# --------------------------
# Clean all examples
# --------------------------
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: check-format-all check-format

check-format-all:
	@for dir in $(SUBDIRS); do \
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

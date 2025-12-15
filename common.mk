# ======================================
# common.mk - shared compiler flags
# ======================================

CXX      := g++
OPTFLAGS ?= -O1 -g           # Safe for ASAN/TSAN (default)

# --------------------------
# Sanitizer selection
# --------------------------
# Default: AddressSanitizer
SANITIZE ?= address

ifeq ($(SANITIZE),address)
    SAN_FLAGS := -fsanitize=address
else ifeq ($(SANITIZE),thread)
    SAN_FLAGS := -fsanitize=thread
else ifeq ($(SANITIZE),undefined)
    SAN_FLAGS := -fsanitize=undefined
else ifeq ($(SANITIZE),)
    SAN_FLAGS :=
else
    $(error Unknown SANITIZE=$(SANITIZE))
endif

# --------------------------
# Compiler / Linker flags
# --------------------------
CXXFLAGS := -std=c++23 -Wall -Wextra $(OPTFLAGS) $(SAN_FLAGS)
LDFLAGS  := $(SAN_FLAGS)

# --------------------------
# Usage notes
# --------------------------
# Local build (default): ASAN enabled
#   $ make
#
# Override for ThreadSanitizer:
#   $ make SANITIZE=thread
#
# Override for UBSAN:
#   $ make SANITIZE=undefined
#
# Disable sanitizers (rare):
#   $ make SANITIZE=
#
# LDFLAGS are automatically applied in example Makefiles:
#   $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

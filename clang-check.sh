#!/bin/bash
set -euo pipefail

# Supported extensions
supported_ext=("c" "h" "cpp" "hpp")

# Check if a file is supported
is_supported_file() {
    local file="$1"
    local ext="${file##*.}"
    for e in "${supported_ext[@]}"; do
        [[ "$ext" == "$e" ]] && return 0
    done
    return 1
}

# Run clang-format in dry-run mode on a single file
format_file() {
    local file="$1"
    if is_supported_file "$file"; then
        echo "Check Formatting $file"
        clang-format --dry-run --Werror "$file"
    else
        echo "Skipping unsupported file: $file"
    fi
}

# Run clang-format on a glob pattern recursively
format_pattern() {
    local pattern="$1"
    # Find files matching the pattern
    find . -type f -iname "$pattern" ! -path "./.git/*" -print0 | while IFS= read -r -d '' file; do
        format_file "$file"
    done
}

# Main
if [ "$#" -eq 0 ]; then
    # Default: format all supported files
    for ext in "${supported_ext[@]}"; do
        format_pattern "*.$ext"
    done
else
    for arg in "$@"; do
        if [ -f "$arg" ]; then
            format_file "$arg"
        else
            # Treat as a pattern
            format_pattern "$arg"
        fi
    done
fi

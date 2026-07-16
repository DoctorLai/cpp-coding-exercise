#!/usr/bin/env bash

set -euo pipefail

# Run the tests
pi=$(./pi)

# Check that the result is numeric and within a reasonable range.
if ! awk -v pi="$pi" 'BEGIN { exit !(pi ~ /^[0-9]+([.][0-9]+)?$/ && pi >= 3.0 && pi <= 3.2) }'; then
    echo "Test failed: pi is out of range: $pi"
    exit 1
fi

echo "Test passed: pi is within range: $pi"

#!/bin/bash

set -ex

# Run the tests
pi=$(./parallel-integral-pi)

# Check that the result is within a reasonable range
if (( $(echo "$pi < 3.0" | bc -l) )) ||
   (( $(echo "$pi > 3.2" | bc -l) )); then
    echo "Test failed: pi is out of range: $pi"
    exit 1
else
    echo "Test passed: pi is within range: $pi"
fi

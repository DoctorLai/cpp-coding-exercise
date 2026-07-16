#!/usr/bin/env bash

set -euo pipefail

output=$(./parallel-integral-pi 100000 6)
pi=${output#pi = }

if ! awk -v pi="$pi" 'BEGIN {
    expected = atan2(0, -1)
    error = pi - expected
    if (error < 0) {
        error = -error
    }
    exit !(error < 0.000000001)
}'; then
    echo "Test failed: inaccurate approximation: $pi"
    exit 1
fi

if ./parallel-integral-pi 0 2 >/dev/null 2>&1; then
    echo "Test failed: zero iterations should be rejected"
    exit 1
fi

echo "Test passed: pi = $pi"

#!/bin/bash

set -ex

./rot47

helloworld=$(./rot47 'w6==@ (@C=5P')

if [ "$helloworld" != "Hello World!" ]; then
    echo "Test failed: expected 'Hello World!' but got '$helloworld'"
    exit 1
fi

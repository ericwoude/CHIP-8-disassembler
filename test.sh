#!/bin/bash

if diff "$PWD/tests/maze.c8" <(./disassembler "$PWD/tests/maze") ; then
    echo "Testing: success"
    exit 0
else
    echo "Testing: failure"
    exit 127
fi
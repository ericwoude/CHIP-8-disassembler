#!/bin/bash

# This file is part of the CHIP-8 disassembler.
# (https://github.com/ericwoude/CHIP-8-disassembler)
#
# The MIT License (MIT)
#
# Copyright © 2022 Eric van der Woude
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the “Software”), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
# NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# Color codes used for pretty printing
green='\033[0;32m'
red='\033[0;31m'
blank='\033[0m'

# Check if the disassembler binary exists
if ! [ -f "./disassembler" ]; then
  echo "Failure: disassembler binary does not exist"
  exit 127
fi

# Search for all test programs and their expected outcome
# binaries. Then, use `diff` to see if the disassembler
# disassembles the program as expected.
echo "Testing..."

failed_tests=0
for test in tests/*.c8; do
  binary=$(echo $test | cut -f 1 -d '.')

  if diff $test <(./disassembler $binary); then
    echo -e "$green  success$blank $test"
  else
    echo -e "$red  failure$blank $test"
    let failed_tests++
  fi
done

# Conclude the tests by presenting the status
if [ $failed_tests -eq 0 ]; then
  echo -e "=>$green all tests succeeded$blank"
  exit 0
else
  if [ $failed_tests -eq 1 ]; then
    echo -e "=>$red ${failed_tests} test failed$blank"
  else
    echo -e "=>$red ${failed_tests} tests failed$blank"
  fi

  exit 127
fi
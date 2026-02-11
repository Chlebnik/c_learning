#!/bin/bash

# Compile the C program
gcc factorial.c -o factorial

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Test case 1: 5! = 120
echo "5" > input.txt
./factorial < input.txt > output.txt
if grep -q "120" output.txt; then
    echo "Test 1 Passed (5! = 120)"
else
    echo "Test 1 Failed! Expected 120."
    rm input.txt output.txt factorial
    exit 1
fi

# Test case 2: 0! = 1
echo "0" > input.txt
./factorial < input.txt > output.txt
if grep -q "1" output.txt; then
    echo "Test 2 Passed (0! = 1)"
else
    echo "Test 2 Failed! Expected 1."
    rm input.txt output.txt factorial
    exit 1
fi

echo "All Tests Passed!"
rm input.txt output.txt factorial
exit 0

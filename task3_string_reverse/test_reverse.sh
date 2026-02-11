#!/bin/bash

# Compile the C program
gcc reverse.c -o reverse

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Test case 1: "hello" -> "olleh"
echo "hello" > input.txt
./reverse < input.txt > output.txt
if grep -q "olleh" output.txt; then
    echo "Test 1 Passed ('hello' -> 'olleh')"
else
    echo "Test 1 Failed! Expected 'olleh'."
    rm input.txt output.txt reverse
    exit 1
fi

# Test case 2: "racecar" -> "racecar"
echo "racecar" > input.txt
./reverse < input.txt > output.txt
if grep -q "racecar" output.txt; then
    echo "Test 2 Passed ('racecar' -> 'racecar')"
else
    echo "Test 2 Failed! Expected 'racecar'."
    rm input.txt output.txt reverse
    exit 1
fi

echo "All Tests Passed!"
rm input.txt output.txt reverse
exit 0

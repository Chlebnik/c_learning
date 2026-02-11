#!/bin/bash

# Compile the C program
gcc hello.c -o hello

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Create a test input file
echo "Alice" > input.txt

# Run the program with the input file
./hello < input.txt > output.txt

# Check if the output matches the expected output
if grep -q "Hello, Alice!" output.txt; then
    echo "Test Passed!"
    rm input.txt output.txt hello
    exit 0
else
    echo "Test Failed!"
    echo "Expected: Hello, Alice!"
    echo "Got:"
    cat output.txt
    rm input.txt output.txt hello
    exit 1
fi

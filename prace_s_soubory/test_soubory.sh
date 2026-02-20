#!/bin/bash

# Compile the C program
SCRIPT_DIR=$(dirname "$0")
cd "$SCRIPT_DIR"

# Create a temporary directory for testing
TEST_DIR=$(mktemp -d)
echo "Running tests in $TEST_DIR"

# Clean up function
cleanup() {
    rm -rf "$TEST_DIR"
}
trap cleanup EXIT

echo "Compiling src/main.c..."
gcc src/main.c -o "$TEST_DIR/main"

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation successful."

# Change to test directory
cd "$TEST_DIR"

# Test Case 1: Identical files, output to screen
echo "Test Case 1: Identical files, output to screen"
echo "Hello World" > cti1.txt
echo "Hello World" > cti2.txt

# Input: O (screen), N (no stats)
printf "O\nN\n" > input.txt

./main < input.txt > output.txt

if grep -q "Pocet nalezenych rozdilu je 0." output.txt; then
    echo "Test 1 Passed"
else
    echo "Test 1 Failed"
    cat output.txt
    exit 1
fi

# Test Case 2: Different files, output to screen
echo "Test Case 2: Different files, output to screen"
echo "Hello World" > cti1.txt
echo "Hello Warld" > cti2.txt
# Difference: 'o' vs 'a' -> 1 difference

printf "O\nN\n" > input.txt

./main < input.txt > output.txt

if grep -q "Pocet nalezenych rozdilu je 1." output.txt; then
    echo "Test 2 Passed"
else
    echo "Test 2 Failed"
    cat output.txt
    exit 1
fi

# Test Case 3: Different files with stats, output to file
echo "Test Case 3: Different files with stats, output to file"
echo "Hello World" > cti1.txt
echo "Hello Warld" > cti2.txt

# Input: S (file), A (stats)
printf "S\nA\n" > input.txt

# Run program
./main < input.txt > output.txt

# Verify zapis.txt
if [ ! -f zapis.txt ]; then
    echo "Test 3 Failed: zapis.txt not created"
    exit 1
fi

if grep -q "Pocet nalezenych rozdilu je 1." zapis.txt; then
    echo "Test 3 (Diff Count) Passed"
else
    echo "Test 3 (Diff Count) Failed"
    cat zapis.txt
    exit 1
fi

# Check for stats in zapis.txt
# "Hello World\n" -> 1 line, 12 chars
if grep -q "Pocet pocet_radku 1, pocet_znaku 12 pro soubor cti1.txt." zapis.txt; then
    echo "Test 3 (Stats) Passed"
else
    echo "Test 3 (Stats) Failed"
    echo "Content of zapis.txt:"
    cat zapis.txt
    exit 1
fi

echo "All Tests Passed!"
exit 0

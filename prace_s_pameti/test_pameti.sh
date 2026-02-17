#!/bin/bash

set -e

# Change directory to the script's location
cd "$(dirname "$0")"

# Compile the C program
gcc src/main.c -o pamet

# Backup original cti.txt
if [ -f cti.txt ]; then
    cp cti.txt cti.txt.bak
fi

# Function to clean up on exit
cleanup() {
    # Restore cti.txt if backup exists
    if [ -f cti.txt.bak ]; then
        mv cti.txt.bak cti.txt
    else
        # If no backup existed, just remove the created cti.txt
        rm -f cti.txt
    fi
    rm -f pamet output.txt expected.txt
}
trap cleanup EXIT

# Generate input and expected output using Python
python3 -c '
import sys

filename = "cti.txt"
expected_filename = "expected.txt"

# Generate 2000 lines to force multiple reallocations
# Start size is 10. Realloc happens at 10, 20, 40, 80...
# 2000 lines should be plenty to test stability.
lines = []
for i in range(2000):
    length = 10 + (i % 100)
    line = "A" * length
    lines.append(line)

with open(filename, "w") as f:
    for line in lines:
        f.write(line + "\n")

with open(expected_filename, "w") as f:
    for i, line in enumerate(lines):
        f.write(f"[{i}] velikost {len(line)}.\n")
    # The C program counts lines after each newline, so it counts an empty line at the end if the file ends with newline
    f.write(f"[{len(lines)}] velikost 0.\n")
'

# Run the program
./pamet > output.txt

# Compare output
if diff -q output.txt expected.txt > /dev/null; then
    echo "Test Passed!"
else
    echo "Test Failed!"
    echo "Diff output:"
    diff output.txt expected.txt
    exit 1
fi

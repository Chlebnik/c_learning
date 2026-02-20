#!/bin/bash
# Integration test for vyhledej_retezec_v_souboru

# Ensure we are in the directory of the script
cd "$(dirname "$0")"

# Compile the program
if [ -f "src/main.c" ]; then
    gcc src/main.c -o search_app
else
    echo "Error: src/main.c not found"
    exit 1
fi

if [ $? -ne 0 ]; then
  echo "Compilation failed"
  exit 1
fi

# Check if test file exists
if [ ! -f "cti.txt" ]; then
    echo "Error: cti.txt not found"
    exit 1
fi

# Create input for the program
# 1. filename: cti.txt
# 2. search string: 10
# This should find "Zkouka 10 siren..." on line 10.
echo -e "cti.txt\n10" > input.txt

# Run the program
./search_app < input.txt > output.txt

# Verify output
# Expected output contains: "Byl nalezen na radkach: 10,"
if grep -q "Byl nalezen na radkach: 10," output.txt; then
  echo "Test passed: Found '10' on line 10"
else
  echo "Test failed: Did not find '10' on line 10"
  cat output.txt
  rm search_app input.txt output.txt
  exit 1
fi

# Test case 2: multiple occurrences
# Search for "32"
echo -e "cti.txt\n32" > input_32.txt
./search_app < input_32.txt > output_32.txt

# Expected: lines 30 and 32
# Line 30: Zkouka 32 ...
# Line 32: Zkouka 32 ...

if grep -q "Byl nalezen na radkach: 30, 32," output_32.txt; then
   echo "Test passed: Found '32' on lines 30, 32"
else
   echo "Test failed: Did not find '32' on lines 30, 32"
   cat output_32.txt
   rm search_app input.txt output.txt input_32.txt output_32.txt
   exit 1
fi

# Clean up
rm search_app input.txt output.txt input_32.txt output_32.txt

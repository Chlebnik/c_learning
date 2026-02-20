#!/bin/bash

# Compile the program
gcc -o retezce src/main.c

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Create a temporary directory
mkdir -p temp_test
cd temp_test

# Create input for zapis
# Filename: output.txt
# Content: line 1, line 2, empty line
echo "output.txt" > input_zapis.txt
echo "Line 1" >> input_zapis.txt
echo "Line 2" >> input_zapis.txt
echo "" >> input_zapis.txt

# Run the program
../retezce zapis < input_zapis.txt

# Check if output.txt exists
if [ ! -f "output.txt" ]; then
    echo "Test failed: output.txt not created."
    cd ..
    rm -rf temp_test
    rm retezce
    exit 1
fi

# Check content
if ! grep -q "Line 1" output.txt || ! grep -q "Line 2" output.txt; then
    echo "Test failed: output.txt content incorrect."
    cat output.txt
    cd ..
    rm -rf temp_test
    rm retezce
    exit 1
fi

echo "Test zapis passed!"

# Clean up
cd ..
rm -rf temp_test
rm retezce

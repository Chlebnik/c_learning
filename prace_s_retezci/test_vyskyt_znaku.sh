#!/bin/bash
# Test for vyskyt_znaku function

# Compile
gcc src/main.c -o retezce
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Function to run test
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_output="$3"

    echo "Running Test: $test_name"
    echo -e "$input" | ./retezce vyskyt > output.txt 2>&1

    if grep -q "$expected_output" output.txt; then
        echo "PASS"
    else
        echo "FAIL"
        echo "Expected: $expected_output"
        echo "Got:"
        cat output.txt
        exit 1
    fi
}

# Test 1: Happy Path
# Input: "hello", search 'l'
# Expected: "1 vyskyt znaku l nalezen ve slove 'hello' na pozici 2."
# We check the first occurrence.
run_test "Happy Path" "hello\nl" "1 vyskyt znaku l nalezen ve slove 'hello' na pozici 2."

# Test 1b: Second occurrence
if grep -q "2 vyskyt znaku l nalezen ve slove 'hello' na pozici 3." output.txt; then
    echo "PASS (Second occurrence)"
else
    echo "FAIL (Second occurrence)"
    cat output.txt
    exit 1
fi

# Test 2: No Occurrence
# Input: "hello", search 'z'
# Expected: No "vyskyt znaku z" line.
echo "Running Test: No Occurrence"
echo -e "hello\nz" | ./retezce vyskyt > output.txt 2>&1
if grep -q "vyskyt znaku z" output.txt; then
    echo "FAIL: Found unexpected occurrence"
    cat output.txt
    exit 1
else
    echo "PASS"
fi

# Test 3: Empty Input
# Input: "\n" (empty string), search 'a'
# Expected: "Zadali jste text:\n" (empty line after)
echo "Running Test: Empty Input"
echo -e "\na" | ./retezce vyskyt > output.txt 2>&1

if ! grep -q "vyskyt znaku" output.txt; then
    echo "PASS"
else
    echo "FAIL"
    cat output.txt
    exit 1
fi

# Test 4: Max Length Input
# MAX_DELKA_POLE is 80.
# The code logic stops reading when index reaches MAX_DELKA_POLE - 2 (78).
# So valid indices are 1..77. Max length is 77 chars.
LONG_STR=$(printf 'a%.0s' {1..77})
echo "Running Test: Max Length Input"
echo -e "${LONG_STR}\na" | ./retezce vyskyt > output.txt 2>&1
# The input is 77 'a's. Position 0 is 'a'.
# 1 vyskyt znaku a nalezen ve slove '...' na pozici 0.
if grep -q "1 vyskyt znaku a nalezen ve slove '$LONG_STR' na pozici 0." output.txt; then
    echo "PASS"
else
    echo "FAIL"
    cat output.txt
    exit 1
fi

# Test 5: Default Behavior (No args)
# Should prompt for filename.
echo "Running Test: Default Behavior"
# Provide empty input
echo "" | ./retezce > output.txt 2>&1
if grep -q "Zadejte nazev souboru, ktery chcete prohledat:" output.txt; then
    echo "PASS"
else
    echo "FAIL"
    cat output.txt
    exit 1
fi

echo "All Tests Passed!"
rm retezce output.txt
exit 0

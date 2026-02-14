#!/bin/bash

# Compile the server
gcc server.c -o server
if [ $? -ne 0 ]; then
    echo "Server compilation failed!"
    exit 1
fi

# Compile the client
gcc client.c -o client
if [ $? -ne 0 ]; then
    echo "Client compilation failed!"
    rm server
    exit 1
fi

# Start the server in the background
./server &
SERVER_PID=$!

# Give the server a moment to start
sleep 1

# Define messages to send
MSG1="Hello_World"
MSG2="Parallel_Networking"
MSG3="Unix_Sockets"

# Run clients concurrently
./client $MSG1 > output1.txt &
PID1=$!
./client $MSG2 > output2.txt &
PID2=$!
./client $MSG3 > output3.txt &
PID3=$!

# Wait for clients to finish
wait $PID1
wait $PID2
wait $PID3

# Kill the server
kill $SERVER_PID
wait $SERVER_PID 2>/dev/null

# Verify outputs
FAILED=0

if grep -q "$MSG1" output1.txt; then
    echo "Test 1 Passed"
else
    echo "Test 1 Failed: Expected $MSG1"
    FAILED=1
fi

if grep -q "$MSG2" output2.txt; then
    echo "Test 2 Passed"
else
    echo "Test 2 Failed: Expected $MSG2"
    FAILED=1
fi

if grep -q "$MSG3" output3.txt; then
    echo "Test 3 Passed"
else
    echo "Test 3 Failed: Expected $MSG3"
    FAILED=1
fi

# Cleanup
rm server client output1.txt output2.txt output3.txt

if [ $FAILED -eq 0 ]; then
    echo "All tests passed!"
    exit 0
else
    echo "Some tests failed."
    exit 1
fi

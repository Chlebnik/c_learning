# Task 4: Parallel Networking

## Goal
Write a concurrent TCP echo server that can handle multiple clients simultaneously.

## Instructions
1.  Open `server.c`.
2.  Implement the `main` function to:
    - Create a TCP socket.
    - Bind the socket to port 8888.
    - Listen for incoming connections.
    - Enter a loop to accept connections.
3.  When a connection is accepted:
    - Fork a new process to handle the client.
    - In the child process:
        - Read messages from the client.
        - Echo the message back to the client.
        - Close the client socket and exit.
    - In the parent process:
        - Close the client socket (it's handled by the child).
        - Continue listening for new connections.
4.  Run `./verify.sh` to compile and verify your solution.

## Hints
- Use `socket()`, `bind()`, `listen()`, `accept()`, `fork()`, `read()`, `write()`, `close()`.
- Remember to handle zombie processes (e.g., using `waitpid` with `WNOHANG` in a signal handler for `SIGCHLD`).

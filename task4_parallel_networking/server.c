#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define PORT 8888
#define BUFFER_SIZE 1024

// TODO: Implement SIGCHLD handler to prevent zombie processes
void sigchld_handler(int s) {
    // ...
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // 1. Create socket
    // TODO: Create a TCP socket
    // Hint: socket(AF_INET, SOCK_STREAM, 0)

    // TODO: Use setsockopt to reuse address/port (optional but recommended)

    // 2. Bind socket to port
    // TODO: Implement binding

    // 3. Listen for connections
    // TODO: Implement listening

    // TODO: Setup signal handler for SIGCHLD

    printf("Server listening on port %d\n", PORT);

    // 4. Accept loop
    while(1) {
        // TODO: Accept connection

        // TODO: Fork a new process to handle the client

            // Child process:
            // TODO: Read from socket
            // TODO: Echo back to socket
            // TODO: Close socket and exit

        // Parent process:
        // TODO: Close client socket
    }

    return 0;
}

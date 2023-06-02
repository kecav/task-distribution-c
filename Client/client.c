#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define THREAD_COUNT 5

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char message[BUFFER_SIZE] = {0};
    char buffer[BUFFER_SIZE] = {0};

    // Create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    // Set address configuration
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from string to binary
    if (inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr)) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    // Interactive communication with the server
    while (1) {
        printf("Enter a message (or 'exit' to quit): ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';

        // Send message to the server
        send(sock, message, strlen(message), 0);
        printf("Message sent to the server\n");

        // Check if the user wants to exit
        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Receive response from the server
        valread = recv(sock, buffer, BUFFER_SIZE, 0);
        printf("Response from server: %s\n", buffer);

        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);
    }

    // Close the socket
    close(sock);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <dirent.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// search file name from directory
void listMatchingFiles(const char *filename, int sock) {
    DIR *directory;
    struct dirent *entry;

    directory = opendir("../Input/");
    if (directory == NULL) {
        printf("Error opening directory.\n");

        // Send message to the server
        char *message = "Could not find the specified file.";
        send(sock, message, strlen(message), 0);
        return;
    }

    while ((entry = readdir(directory)) != NULL) {
        if (strstr(entry->d_name, filename) != NULL) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(directory);
}


// run shell command to execute c code
void compile_files(){
    // Compile the C file
    system("gcc process_csv.c -o process_csv");

    // Execute the compiled file and redirect the output
    system("./process_csv > ../Output/data.txt");

}

// main
int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    // char message[BUFFER_SIZE] = {0};
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
        
        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);
        // Receive response from the server
        valread = recv(sock, buffer, BUFFER_SIZE, 0);

        // if server exits
        if(strcmp(buffer, "exit")==0)
            break;
        
        // printing the received filename
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline character
        printf("Received filename : %s\n", buffer);

        // check if file exists in directory
        listMatchingFiles(buffer, sock);
        printf("Waiting for another file...\n");
    }

    // Close the socket
    close(sock);

    return 0;
}

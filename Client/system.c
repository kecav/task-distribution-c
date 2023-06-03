#include <stdio.h>
#include <stdlib.h>

int main() {
    // Run a shell command
    int result = system("gcc process_csv.c -o process_csv");  // shell command

    // Check the return value of system() for success or failure
    if (result == -1) {
        printf("Failed to execute the command.\n");
    } else {
        printf("Command executed successfully.\n");
    }

    return 0;
}

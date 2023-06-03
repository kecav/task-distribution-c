#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int age;
    char email[100];
} Person;


int main() {
    // Open the CSV file for reading
    FILE* file = fopen("../Input/data.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Skip the header row
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);

    // Process the CSV file and calculate the average age
    int totalAge = 0;
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Parse the CSV row and extract the data
        char* name = strtok(buffer, ",");
        char* ageStr = strtok(NULL, ",");
        char* email = strtok(NULL, ",");

        // Convert the age string to an integer
        int age = atoi(ageStr);

        // Update the total age and count
        totalAge += age;
        count++;
    }

    // Close the file
    fclose(file);

    // Calculate the average age
    double averageAge = (double)totalAge / count;

    // Display the result
    printf("Average Age: %.2f\n", averageAge);

    return 0;
}

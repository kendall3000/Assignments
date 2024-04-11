/*
* File: wordcount.c
* Kendall Ramos ... YOU NEED TO IMPLEMENT THE FUNCTIONS HERE....
*
* ....
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // For isspace() function
#include <unistd.h> // For getpid() function


// Function to count words in a file
int countWords(FILE *file) {
    int wordCount = 0;
    int inWord = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            inWord = 0;
        } else {
            if (!inWord) {
                wordCount++;
                inWord = 1;
            }
        }
    }

    return wordCount;
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *file = fopen(argv[1], "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Count words in the file
    int wordCount = countWords(file);

    // Close the file
    fclose(file);

    // Print the word count
    printf("wordcount with process pid_%d counted words in %s: number of words is %d\n", getpid(), argv[1], wordCount);

    return 0;
}

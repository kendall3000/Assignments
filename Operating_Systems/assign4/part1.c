#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 8

unsigned long LA, PA;
int PT[PAGE_TABLE_SIZE] = {2, 4, 1, 7, 3, 5, 6, -1}; // Fixed page table

// Function to perform address translation
void translateAddress(FILE *outfile) {
    unsigned long page_number = (LA >> 12) & (PAGE_TABLE_SIZE - 1); // Assuming a power of 2 page table size
    unsigned long offset = LA & (PAGE_SIZE - 1);

    if (PT[page_number] == -1) {
        printf("Page fault for LA = %lx\n", LA);
        // Handle page fault (not implemented in this example)
        // You may want to load the page from disk into physical memory
    } else {
        // Construct physical address
        PA = (PT[page_number] << 12) | offset;

        // Write physical address to outfile
        if (fwrite(&PA, sizeof(unsigned long), 1, outfile) != 1) {
            perror("Error writing to output file");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file in binary mode
    FILE *infile = fopen(argv[1], "rb");
    if (!infile) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Open output file in binary mode
    FILE *outfile = fopen(argv[2], "wb");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile); // Close input file before exiting
        exit(EXIT_FAILURE);
    }

    // Read each logical address, perform address translation, and write to outfile
    while (fread(&LA, sizeof(unsigned long), 1, infile) == 1) {
        // Address translation logic
        translateAddress(outfile);
    }

    // Close files
    fclose(infile);
    fclose(outfile);

    return 0;
}

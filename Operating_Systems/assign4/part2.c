#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 32
#define NUM_FRAMES 8

unsigned long LA, PA;
int global_counter = 0;

// Structure for Page Table Entry (PTE)
typedef struct {
    int valid_bit;
    int frame_number;
    int counter; // For LRU page replacement
} PTE;

PTE PT[PAGE_TABLE_SIZE]; // Dynamic page table
int free_frames[NUM_FRAMES] = {1, 1, 1, 1, 1, 1, 1, 1}; // 1: Free, 0: Allocated

// Function to initialize the page table
void initializePageTable() {
    for (int i = 0; i < PAGE_TABLE_SIZE; ++i) {
        PT[i].valid_bit = 0;
        PT[i].frame_number = -1;
        PT[i].counter = 0;
    }
}

// Function to perform address translation with page replacement
void translateAddress() {
    unsigned long page_number = (LA >> 12) & (PAGE_TABLE_SIZE - 1);
    unsigned long offset = LA & (PAGE_SIZE - 1);

    if (PT[page_number].valid_bit == 1) {
        // Page is in memory, perform translation
        PT[page_number].counter = global_counter++; // Update LRU counter
        PA = (PT[page_number].frame_number << 12) | offset;
    } else {
        // Page fault, find a free frame or perform page replacement
        int free_frame_index = -1;

        for (int i = 0; i < NUM_FRAMES; ++i) {
            if (free_frames[i] == 1) {
                free_frame_index = i;
                break;
            }
        }

        if (free_frame_index != -1) {
            // Allocate a free frame
            PT[page_number].valid_bit = 1;
            PT[page_number].frame_number = free_frame_index;
            PT[page_number].counter = global_counter++;

            free_frames[free_frame_index] = 0; // Mark frame as allocated

            // Perform translation
            PA = (PT[page_number].frame_number << 12) | offset;
        } else {
            // Perform LRU page replacement
            int min_counter = PT[0].counter;
            int min_index = 0;

            for (int i = 1; i < PAGE_TABLE_SIZE; ++i) {
                if (PT[i].counter < min_counter) {
                    min_counter = PT[i].counter;
                    min_index = i;
                }
            }

            // Update page table for LRU page replacement
            free_frames[PT[min_index].frame_number] = 1; // Mark the replaced frame as free
            PT[min_index].valid_bit = 1;
            PT[min_index].frame_number = free_frame_index; // Update frame number here
            PT[min_index].counter = global_counter++;

            // Perform translation
            PA = (PT[min_index].frame_number << 12) | offset;
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        printf("Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    // Initialize page table
    initializePageTable();

    // Open input file in binary mode
    FILE *infile = fopen(argv[1], "rb");
    if (!infile) {
        perror("Error opening input file");
        return 1;
    }

    // Open output file in binary mode
    FILE *outfile = fopen(argv[2], "wb");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile); // Close input file before exiting
        return 1;
    }

    // Read each logical address, perform address translation with page replacement, and write to outfile
    while (fread(&LA, sizeof(unsigned long), 1, infile) == 1) {
        // Address translation logic with page replacement
        translateAddress();

        // Write physical address to outfile
        if (fwrite(&PA, sizeof(unsigned long), 1, outfile) != 1) {
            perror("Error writing to output file");
            fclose(infile);
            fclose(outfile);
            return 1;
        }
    }

    // Close files
    fclose(infile);
    fclose(outfile);

    return 0;
}


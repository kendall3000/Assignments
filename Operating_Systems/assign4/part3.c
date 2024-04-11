#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valid_bit;
    int frame_number;
    int counter;
} PTE;

unsigned long LA, PA;
PTE *PT;
int *free_frames;
int *revmap;
int *LRUcount;
int global_counter = 0;

void initializePageTable(unsigned long num_pages) {
    PT = (PTE *)malloc(num_pages * sizeof(PTE));
    free_frames = (int *)malloc(num_pages * sizeof(int));
    revmap = (int *)malloc(num_pages * sizeof(int));
    LRUcount = (int *)malloc(num_pages * sizeof(int));

    if (!PT || !free_frames || !revmap || !LRUcount) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i < num_pages; ++i) {
        PT[i].valid_bit = 0;
        PT[i].frame_number = -1;
        free_frames[i] = 1;
        revmap[i] = -1;
        LRUcount[i] = 0;
    }
}

void cleanup() {
    free(PT);
    free(free_frames);
    free(revmap);
    free(LRUcount);
}

void translateAddress(unsigned long LA, unsigned long *PA, unsigned long d, unsigned long p, unsigned long f) {
    unsigned long pnum = LA >> d;
    unsigned long dnum = LA & ((1UL << d) - 1);

    if (pnum < (1UL << p)) {
        if (PT[pnum].valid_bit == 1) {
            // Page is in memory, perform translation
            PT[pnum].counter = global_counter++;
            *PA = (PT[pnum].frame_number << f) | dnum;
        } else {
            // Page fault, handle accordingly (e.g., load the page from disk)
            int free_frame_index = -1;
            for (unsigned long i = 0; i < p; ++i) {
                if (free_frames[i] == 1) {
                    free_frame_index = i;
                    break;
                }
            }

            if (free_frame_index != -1) {
                // Allocate a free frame
                PT[pnum].valid_bit = 1;
                PT[pnum].frame_number = free_frame_index;
                PT[pnum].counter = global_counter++;

                free_frames[free_frame_index] = 0; // Mark frame as allocated
                revmap[free_frame_index] = pnum;   // Update reverse mapping
                LRUcount[pnum] = global_counter++;

                // Perform translation
                *PA = (PT[pnum].frame_number << f) | dnum;
            } else {
                // Perform LRU page replacement
                int min_counter = LRUcount[0];
                int min_index = 0;

                for (unsigned long i = 1; i < p; ++i) {
                    if (LRUcount[i] < min_counter) {
                        min_counter = LRUcount[i];
                        min_index = i;
                    }
                }

                // Update page table for LRU page replacement
                free_frames[PT[revmap[min_index]].frame_number] = 1; // Mark the replaced frame as free
                PT[revmap[min_index]].valid_bit = 0;                // Invalidate old entry
                PT[revmap[min_index]].frame_number = free_frame_index;
                PT[revmap[min_index]].counter = global_counter++;
                revmap[free_frame_index] = pnum; // Update reverse mapping
                LRUcount[pnum] = global_counter++;

                // Perform translation
                *PA = (PT[revmap[min_index]].frame_number << f) | dnum;
            }
        }
    } else {
        // Invalid page number, handle accordingly
        *PA = -1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s BytesPerPage SizeOfVirtualMemory SizeOfPhysicalMemory SequenceFile OutputFile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    unsigned long BytesPerPage = atoi(argv[1]);
    unsigned long SizeOfVirtualMemory = atoi(argv[2]);
    unsigned long SizeOfPhysicalMemory = atoi(argv[3]);
    unsigned long d = 0, p = 0, f = 0;

    // Calculate d, p, and f based on the provided parameters
    while ((1UL << d) != BytesPerPage)
        d++;
    while ((1UL << p) != SizeOfVirtualMemory)
        p++;
    while ((1UL << f) != SizeOfPhysicalMemory)
        f++;

    // Calculate the number of pages
    unsigned long num_pages = 1UL << p;

    // Initialize page table
    initializePageTable(num_pages);

    // Open input file in binary mode
    FILE *infile = fopen(argv[4], "rb");
    if (!infile) {
        perror("Error opening input file");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Open output file in binary mode
    FILE *outfile = fopen(argv[5], "wb");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile);
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Read each logical address, perform address translation, and write to outfile
    while (fread(&LA, sizeof(unsigned long), 1, infile) == 1) {
        // Address translation logic
        translateAddress(LA, &PA, d, p, f);

        // Write physical address to outfile
        if (fwrite(&PA, sizeof(unsigned long), 1, outfile) != 1) {
            perror("Error writing to output file");
            fclose(infile);
            fclose(outfile);
            cleanup();
            exit(EXIT_FAILURE);
        }
    }

    // Close files and cleanup
    fclose(infile);
    fclose(outfile);
    cleanup();

    return 0;
}

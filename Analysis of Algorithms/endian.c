//#include <stdio.h>

int isLittleEndian() {
    unsigned int x = 1;
    char *c = (char *)&x;

    // If the least significant byte is stored in the first memory location, it's little endian
    if (*c) {
        return 1; // little endian
    } else {
        return 0; // big endian
    }
}

int main() {
    if (isLittleEndian()) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    return 0;
}
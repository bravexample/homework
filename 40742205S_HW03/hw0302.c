// A program to print the directory tree of a zip file

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Macro to print the help message
#define PRINT_HELP printf("Usage: ./hw0305 [OPTION]...\n" \
                          "Example: ./hw0305 -d test.zip\n" \
                          "-a: default, the display order should be file name ASCII ascending order.\n" \
                          "-d: the display order should be file name ASCII descending order.\n")

// Main
int main(int argc, char **argv) {
    // Variables
    char *filename = NULL;
    int32_t order = 0;
    // Check for arguments
    switch (argc) {
        // One argument
        case 2:
            // Set filename
            filename = argv[1];
            break;
        case 3:
            // Check for argument
            if (!strcmp(argv[1], "-a"))
                order = 0;
            else if (!strcmp(argv[1], "-d"))
                order = 1;
            else {
                PRINT_HELP;
                return 1;
            }

            // Set filename
            filename = argv[2];
            break;
        // More than one argument
        default:
            PRINT_HELP;
            return 0;
    }

    // Open the file
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    return 0;
}
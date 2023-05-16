// A program using xor to encrypt a message.

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Set unsigned char abbr
typedef unsigned char uchar;

// Main
int main(int argc, char **argv) {
    // Move to first argument
    argv++;
    argc--;

    // Check for flags
    if (!argc || !(!strcmp(*argv, "-d") || !strcmp(*argv, "-e")))
        return -1;

    // Move to next argument
    argv++;
    argc--;

    // Check for flag
    if (!argc)
        return -1;

    // Key file name
    char *key_filename = NULL;
    // Input file name
    char *input_filename = NULL;
    // Output file name
    char *output_filename = NULL;

    // A loop to get input and output file names
    while (argc) {
        if (!strcmp(*argv, "-k")) {
            // Move to next argument
            argv++;
            argc--;

            // Check for argument and filename
            if (!argc || key_filename)
                return -1;
            
            // Set key file name
            key_filename = *argv;
        }
        else if (!strcmp(*argv, "-i")) {
            // Move to next argument
            argv++;
            argc--;

            // Check for argument and filename
            if (!argc || input_filename)
                return -1;

            // Set input file name
            input_filename = *argv;
        }
        else if (!strcmp(*argv, "-o")) {
            // Move to next argument
            argv++;
            argc--;

            // Check for argument
            if (!argc || output_filename)
                return -1;

            // Set output file name
            output_filename = *argv;
        }
        else
            return -1;

        // Move to next flag
        argv++;
        argc--;
    }

    // Filename missing
    if (!key_filename || !input_filename || !output_filename)
        return -1;

    // Open key file
    FILE *key_file = fopen(key_filename, "rb");
    // Check for errors
    if (!key_file)
        return -1;
    // Get the size of the key file
    fseek(key_file, 0, SEEK_END);
    int key_file_size = ftell(key_file);
    // Reset the file position
    fseek(key_file, 0, SEEK_SET);
    // Allocate memory for the key file
    uchar *key = malloc(key_file_size);
    // Read key file and check for errors
    if (fread(key, 1, key_file_size, key_file) != key_file_size)
        return -1;
    // Close key file
    fclose(key_file);
    
    // Open and read input file
    FILE *input_file = fopen(input_filename, "rb");
    // Check for errors
    if (!input_file)
        return -1;
    // Get the size of the input file
    fseek(input_file, 0, SEEK_END);
    int input_file_size = ftell(input_file);
    // Reset the file position
    fseek(input_file, 0, SEEK_SET);
    // Allocate memory for the input file
    uchar *input = malloc(input_file_size);
    // Read input file and check for errors
    if (fread(input, 1, input_file_size, input_file) != input_file_size)
        return -1;
    // Close input file
    fclose(input_file);

    // Encrypt or decrypt
    for (int i = 0, j = 0; i < input_file_size; i++, j++) {
        if (j >= key_file_size)
            j = 0;
        
        input[i] ^= key[j];
    }

    // Open output file
    FILE *output_file = fopen(output_filename, "wb");
    // Check for errors
    if (!output_file)
        return -1;
    // Write output file
    fwrite(input, 1, input_file_size, output_file);
    // Close output file
    fclose(output_file);

    // Free memory
    free(key);
    free(input);

    // Exit
    return 0;
}
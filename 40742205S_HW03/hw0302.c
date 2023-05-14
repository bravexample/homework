// A program to list of all files and entries in a zip file

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

// Disable the auto alignment of the structure
#pragma pack(1)

// Structures for files and entries in zip file
// Central directory file header
typedef struct {
    uint32_t signature;
    uint16_t version_made_by;
    uint16_t version_needed_to_extract;
    uint16_t flag;
    uint16_t compression;
    uint16_t last_mod_time;
    uint16_t last_mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_length;
    uint16_t extra_field_length;
    uint16_t file_comment_length;
    uint16_t disk_number_start;
    uint16_t internal_file_attributes;
    uint32_t external_file_attributes;
    uint32_t relative_offset_of_local_header;
} CENTRAL_DIRECTORY_FILE_HEADER;

// End of central directory record
typedef struct {
    uint32_t signature;
    uint16_t disk_number;
    uint16_t disk_number_with_start_of_central_directory;
    uint16_t number_of_entries_in_the_central_directory_on_this_disk;
    uint16_t total_number_of_entries_in_the_central_directory;
    uint32_t size_of_the_central_directory;
    uint32_t offset_of_start_of_central_directory_with_respect_to_the_starting_disk_number;
    uint16_t zip_file_comment_length;
} END_OF_CENTRAL_DIRECTORY_RECORD;

// Print function of filenames
void print_filenames(char **filenames, int32_t number_of_entries_in_the_central_directory, int32_t order) {
    // Sort the filenames
    for (int32_t i = 0; i < number_of_entries_in_the_central_directory; i++) {
        for (int32_t j = i + 1; j < number_of_entries_in_the_central_directory; j++) {
            if (!order) {
                if (strcmp(filenames[i], filenames[j]) > 0) {
                    char *temp = filenames[i];
                    filenames[i] = filenames[j];
                    filenames[j] = temp;
                }
            }
            else {
                if (strcmp(filenames[i], filenames[j]) < 0) {
                    char *temp = filenames[i];
                    filenames[i] = filenames[j];
                    filenames[j] = temp;
                }
            }
        }
    }
    
    // Print the filenames
    for (int32_t i = 0; i < number_of_entries_in_the_central_directory; i++) {
        // Print the first character
        printf("+-- %c", filenames[i][0]);
        // Print the rest of the filename
        for (int32_t j = 1; filenames[i][j]; j++)
            printf("%c", filenames[i][j]);
        printf("\n");
    }    
}

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

    // Read the entries and files in zip file
    CENTRAL_DIRECTORY_FILE_HEADER central_directory_file_header;
    END_OF_CENTRAL_DIRECTORY_RECORD end_of_central_directory_record;
    // Read the end of central directory record
    fseek(fp, -sizeof(END_OF_CENTRAL_DIRECTORY_RECORD), SEEK_END);
    if (!fread(&end_of_central_directory_record, sizeof(END_OF_CENTRAL_DIRECTORY_RECORD), 1, fp)) {
        perror("fread");
        return 1;
    }
    // Read the central directory file header
    // Malloc array to store the filenames
    char **filenames = (char **)malloc(sizeof(char *) * end_of_central_directory_record.total_number_of_entries_in_the_central_directory);
    fseek(fp, end_of_central_directory_record.offset_of_start_of_central_directory_with_respect_to_the_starting_disk_number, SEEK_SET);
    for (int32_t i = 0; i < end_of_central_directory_record.total_number_of_entries_in_the_central_directory; i++) {
        if (!fread(&central_directory_file_header, sizeof(CENTRAL_DIRECTORY_FILE_HEADER), 1, fp)) {
            perror("fread");
            return 1;
        }

        // Malloc memory for the filename
        filenames[i] = (char *)malloc(sizeof(char) * (central_directory_file_header.filename_length + 1));
        // Read the filename
        if (!fread(filenames[i], sizeof(char), central_directory_file_header.filename_length, fp)) {
            perror("fread");
            return 1;
        }
        // Add the null terminator
        filenames[i][central_directory_file_header.filename_length] = '\0';

        // Skip the extra field and file comment
        fseek(fp, central_directory_file_header.extra_field_length + central_directory_file_header.file_comment_length, SEEK_CUR);
    }

    // Print the filenames
    print_filenames(filenames, end_of_central_directory_record.total_number_of_entries_in_the_central_directory, order);

    return 0;
}
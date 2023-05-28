// a program to hide files in a bmp

// includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// cancel auto alignment for struct
#pragma pack(1)

// struct for the bmp header
typedef struct {
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
} BMP_HEADER;

// macro for help message
#define PRINT_HELP printf("Usage:\n" \
                          "\tTo hide a file in a bmp file:\n" \
                          "\t./hw0404 -i <file to hide> <bmp file to hide in>\n" \
                          "\tTo extract all file from a bmp file:\n" \
                          "\t./hw0404 -e <bmp file to extract from>\n")

// main
int main(int argc, char **argv) {
    // check arguments
    if (argc < 3) {
        PRINT_HELP;
        return 0;
    }

    // move to first argument
    argc--; argv++;

    // get arguments
    char *bmp_file_name = NULL;
    char *file_name = NULL;
    uint32_t file_name_len = 0;
    char mode = 0;
    while (argc > 0) {
        if (!strcmp(*argv, "-i")) {
            if (argc > 2) {
                argc--; argv++;
            }
            else {
                PRINT_HELP;
                return 0;
            }

            if (file_name == NULL) {
                file_name = *argv;
                file_name_len = strlen(file_name);
            }
            else {
                PRINT_HELP;
                return 0;
            }

            if (mode == 0) {
                mode = 1;
            }
            else {
                PRINT_HELP;
                return 0;
            }
        }
        else if (!strcmp(*argv, "-e")) {
            if (argc == 2) {
                argc--; argv++;
            }
            else {
                PRINT_HELP;
                return 0;
            }

            if (bmp_file_name == NULL) {
                bmp_file_name = *argv;
            }
            else {
                PRINT_HELP;
                return 0;
            }

            if (mode == 0) {
                mode = 2;
            }
            else {
                PRINT_HELP;
                return 0;
            }
        }
        else {
            if (bmp_file_name == NULL) {
                bmp_file_name = *argv;
            }
            else {
                PRINT_HELP;
                return 0;
            }
        }

        argc--; argv++;
    }

    // open bmp file
    FILE *bmp_file = fopen(bmp_file_name, "rb+");

    switch (mode) {
        case 1:
            // move to the end of the file
            fseek(bmp_file, 0, SEEK_END);
            // write the information of the hidden file
            fwrite(&file_name_len, sizeof(uint32_t), 1, bmp_file);
            // write the size of the file
            FILE *file = fopen(file_name, "rb");
            fseek(file, 0, SEEK_END);
            uint32_t file_size = ftell(file);
            fwrite(&file_size, sizeof(uint32_t), 1, bmp_file);
            // write the file name
            fwrite(file_name, sizeof(char), file_name_len, bmp_file);
            // write the file
            fseek(file, 0, SEEK_SET);
            while (file_size  > 0) {
                char c = fgetc(file);
                fputc(c, bmp_file);
                file_size--;
            }
            fclose(file);
            break;
        case 2: {
            // move to the end of the bmp file
            BMP_HEADER bmp_header;
            if (fread(&bmp_header, sizeof(BMP_HEADER), 1, bmp_file) != 1) {
                printf("Error: cannot read bmp header\n");
                return 0;
            }
            fseek(bmp_file, bmp_header.size, SEEK_SET);
            while (1) {
                // read the file name length
                if (fread(&file_name_len, sizeof(uint32_t), 1, bmp_file) != 1) {
                    if (feof(bmp_file)) {
                        break;
                    }
                    else {
                        printf("Error: cannot read file name length\n");
                        return 0;
                    }
                }
                // read the file size
                if (fread(&file_size, sizeof(uint32_t), 1, bmp_file) != 1) {
                    printf("Error: cannot read file size\n");
                    return 0;
                }
                // read the file name
                file_name = malloc(file_name_len + 1);
                if (fread(file_name, sizeof(char), file_name_len, bmp_file) != file_name_len) {
                    printf("Error: cannot read file name\n");
                    return 0;
                }
                // open the file
                FILE *file = fopen(file_name, "wb");
                // write the file
                while (file_size > 0) {
                    char c = fgetc(bmp_file);
                    fputc(c, file);
                    file_size--;
                }
                fclose(file);
                free(file_name);
            }
        }
    }

    // exit
    return 0;
}
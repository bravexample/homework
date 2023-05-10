// A program to mosaic a certain area of a picture

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Macro for the options
#define X       1
#define Y       2
#define WIDTH   4
#define HEIGHT  8
#define INPUT   16
#define OUTPUT  32
#define NUMBER  64

// Structure for the header of the bmp file
// Cancel the auto alimentation of the structure
#pragma pack(1)
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

// Structure for the pixel
typedef struct {
    uint8_t	b;
    uint8_t	g;
    uint8_t	r;
} PIXEL;

static inline void print_help() {
    printf("Usage: ./hw0303 [OPTION]...\n");
    printf("Example: ./hw0303 -x 500 -y 300 -w 100 -h 100 -n 10 -i spy.bmp -o spy2.bmp\n");
    printf("-x: mandatory, x value.\n");
    printf("-y: mandatory, y value.\n");
    printf("-w, −−width: mandatory, width value.\n");
    printf("-h, −−height: mandatory, height value.\n");
    printf("-i, −−input: mandatory, input file.\n");
    printf("-o, −−output: optional, output file.\n");
    printf("-n, −−number: optional, number value.\n");
}

// Main
int main(int argc, char *argv[]) {
    // Variables
    int x, y, width, height, number = 2;
    char *input, *output = NULL;
    // move to first option
    argc--;
    argv++;

    // Get the options
    int option = 0;
    while (argc > 0) {
        if (!strcmp(argv[0], "-x")) {
            option |= X;
            // Check argument
            if (argc < 2) {
                print_help();
                return 1;
            }
            x = atoi(argv[1]);
        }
        else if (!strcmp(argv[0], "-y")) {
            option |= Y;
            // Check argument
            if (argc < 2) {
                print_help();
                return 1;
            }
            y = atoi(argv[1]);
        }
        else if (!strcmp(argv[0], "-w") || !strcmp(argv[0], "--width")) {
            option |= WIDTH;
            // Check argument
            if (argc < 2) {
                print_help();
                return 1;
            }
            width = atoi(argv[1]);
        }
        else if (!strcmp(argv[0], "-h") || !strcmp(argv[0], "--height")) {
            option |= HEIGHT;
            // Check argument
            if (argc < 2) {
                print_help();
                return 1;
            }
            height = atoi(argv[1]);
        }
        else if (!strcmp(argv[0], "-i") || !strcmp(argv[0], "--input")) {
            option |= INPUT;
            // Check argument
            if (argc < 2) {
                print_help();
                return 1;
            }
            input = argv[1];
        }
        else if (!strcmp(argv[0], "-o") || !strcmp(argv[0], "--output")) {
            option |= OUTPUT;
            // Check argument
            if (argc < 2) {
                print_help();
                return 1;
            }
            output = argv[1];
        }
        else if (!strcmp(argv[0], "-n") || !strcmp(argv[0], "--number")) {
            option |= NUMBER;
            // Check argument
            if (argc < 2) {
                print_help();
                return 1;
            }
            number = atoi(argv[1]);
        }
        else {
            print_help();
            return 1;
        }

        argc -= 2;
        argv += 2;
    }

    if ((option & (X | Y | WIDTH | HEIGHT | INPUT)) != (X | Y | WIDTH | HEIGHT | INPUT)) {
        print_help();
        return 1;
    }

    if (number < 1) {
        printf("I can't get the average of %d numbers of pixels.\n", number);
        return 1;
    }

    // Open the bmp file
    FILE *fp = fopen(input, "rb");
    if (!fp) {
        perror("Error ");
        return 1;
    }
    // Read the header
    BMP_HEADER header;
    if (!fread(&header, sizeof(BMP_HEADER), 1, fp)) {
        perror("Error ");
        return 1;
    }

    if (y + width > header.width || x + height > header.height) {
        printf("Error: The requested area is out of the picture.\n");
        return 1;
    }

    // A 2D array for the pixels
    PIXEL **pixels = malloc(sizeof(PIXEL *) * header.height);
    for (int i = 0; i < header.height; i++) {
        pixels[i] = malloc(sizeof(PIXEL) * header.width);
        if (!pixels[i]) {
            perror("Error ");
            return 1;
        }
        // Read the pixels from the bmp file
        if (!fread(pixels[i], sizeof(PIXEL), header.width, fp)) {
            perror("Error ");
            return 1;
        }
    }

    // Close the bmp file
    fclose(fp);

    for (int i = y; i < y + width; i += number) {
        for (int j = x; j < x + height; j += number) {
            // Setup temp variables
            int blue = 0, green = 0, red = 0, count = 0;
            // Sum the pixels in n * n area
            for (int k = 0; (k < number) && ((i + k) < (y + width)); k++) {
                for (int l = 0; (l < number) && ((j + l) < (x + height)); l++) {
                    int real_x = header.height - (j + l);
                    blue += pixels[real_x][i + k].b;
                    green += pixels[real_x][i + k].g;
                    red += pixels[real_x][i + k].r;
                    count++;
                }
            }
            // Average the sum
            if (count) {
                blue /= count;
                green /= count;
                red /= count;
            }
            // Set the average to the pixels in n * n area
            for (int k = 0; (k < number) && ((i + k) < (y + width)); k++) {
                for (int l = 0; (l < number) && ((j + l) < (x + height)); l++) {
                    int real_x = header.height - (j + l);
                    pixels[real_x][i + k].b = blue;
                    pixels[real_x][i + k].g = green;
                    pixels[real_x][i + k].r = red;
                }
            }
        }
    }

    // Open the bmp file to output
    if (!output)
        fp = fopen("output.bmp", "wb");
    else
        fp = fopen(output, "wb");

    if (!fp) {
        perror("Error ");
        return 1;
    }

    // Write the header
    if (!fwrite(&header, sizeof(BMP_HEADER), 1, fp)) {
        perror("Error ");
        return 1;
    }

    // Write the pixels
    for (int i = 0; i < header.height; i++)
        if (!fwrite(pixels[i], sizeof(PIXEL), header.width, fp)) {
            perror("Error ");
            return 1;
        }
    
    return 0;
}
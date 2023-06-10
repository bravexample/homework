// a program to generate a BMP about golden ratio squares

// include c std
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// disable auto alignment of structs
#pragma pack(1)

// header of BMP file
typedef struct
{
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
} sBmpHeader;

// struct for pixel
typedef struct {
    uint8_t	b;
    uint8_t	g;
    uint8_t	r;
} sPixel;

// structure for coordinate
typedef struct {
    int x;
    int y;
} sCoor;

// global variables
int		n;
int		width;
int		height;
sPixel	**pixels;
char	*output_name;

// recursive function for generate squares
void drawSquare(sCoor start, sCoor end, sCoor butleft, sCoor upright, int mode) {
    // check condition
    if (n > 0) {
        switch(mode) {
            case 0:
                // draw a vertical black line to up
                for (int i = start.y; i < end.y; i++) {
                    pixels[i][start.x].r = 0;
                    pixels[i][start.x].g = 0;
                    pixels[i][start.x].b = 0;
                }
                break;
            case 1:
                // draw a horizontal black line right
                for (int i = start.x; i < end.x; i++) {
                    pixels[start.y][i].r = 0;
                    pixels[start.y][i].g = 0;
                    pixels[start.y][i].b = 0;
                }
                break;
            case 2:
                // draw a vertical black line to down
                for (int i = start.y; i > end.y; i--) {
                    pixels[i][start.x].r = 0;
                    pixels[i][start.x].g = 0;
                    pixels[i][start.x].b = 0;
                }
                break;
            case 3:
                // draw a horizontal black line left
                for (int i = start.x; i > end.x; i--) {
                    pixels[start.y][i].r = 0;
                    pixels[start.y][i].g = 0;
                    pixels[start.y][i].b = 0;
                }
                break;
        }

        // recursive call
        n--;
        switch(mode) {
            case 0: {
                upright.y = butleft.y;
                butleft = end;
                start.y = end.y - (upright.x - end.x);
                end.y = start.y;
                end.x = upright.x;
                mode = 1;
                break;
            }
            case 1: {
                upright.x = butleft.x;
                butleft = end;
                start.x = end.x - (end.y - upright.y);
                end.x = start.x;
                end.y = upright.y;
                mode = 2;
                break;
            }
            case 2: {
                upright.y = butleft.y;
                butleft = end;
                start.y = end.y + (end.x - upright.x);
                end.y = start.y;
                end.x = upright.x;
                mode = 3;
                break;
            }
            case 3: {
                upright.x = butleft.x;
                butleft = end;
                start.x = end.x + (upright.y - end.y);
                end.x = start.x;
                end.y = upright.y;
                mode = 0;
                break;
            }
        }
        drawSquare(start, end, butleft, upright, mode);
    }
}

// macro for printing help
#define printHelp() printf("Options:\n" \
                           "\t-a <int> Mandatory. Set the value of a where the unit is pixel.\n" \
                           "\t\t\tRange: 100 - 2000\n" \
                           "\t-n <int> Mandatory. Set the value of n.\n" \
                           "\t-o, --output Set the output file name.\n" \
                           "\t-h, --help Display this description.\n")

// check arguments
int checkArgs(int argc, char **argv) {
    if (argc < 5) {
        return 0;
    }

    while (argc > 2) {
        // move to next argument
        argc--; argv++;

        if (strcmp(*argv, "-a") == 0) {
            argc--; argv++;
            height = atoi(*argv);
            if (height < 100 || height > 2000) {
                return 0;
            }
            // height / width = golden ratio
            width = ((1 + sqrt(5)) * height) / 2;
        }
        else if (strcmp(*argv, "-n") == 0) {
            argc--; argv++;
            n = atoi(*argv);
            if (n < 1) {
                return 0;
            }
        }
        else if (strcmp(*argv, "-o") == 0 || strcmp(*argv, "--output") == 0) {
            argc--; argv++;
            output_name = *argv;
        }
    }
}

// main function
int main(int argc, char **argv) {
    // check arguments
    if (!checkArgs(argc, argv)) {
        printHelp();
        return -1;
    }

    // check mandatory arguments
    if (!width || !n) {
        printHelp();
        return -1;
    }

    // check output file name
    if (!output_name) {
        output_name = "output.bmp";
    }

    // generate pixels
    pixels = (sPixel **)malloc(sizeof(sPixel *) * height);
    for (int i = 0; i < height; i++) {
        pixels[i] = (sPixel *)malloc(sizeof(sPixel) * width);
        // set all pixels to white
        for (int j = 0; j < width; j++) {
            pixels[i][j].r = 255;
            pixels[i][j].g = 255;
            pixels[i][j].b = 255;
        }
    }

    // call the recursive function to draw squares
    sCoor start = {height, 0};
    sCoor end = {height, height};
    sCoor butleft = {0, 0};
    sCoor upright = {width, height};
    drawSquare(start, end, butleft, upright, 0);

    // create a bmp header for the pixels
    sBmpHeader header;
    header.bm[0] = 'B';
    header.bm[1] = 'M';
    header.size = 54 + width * height * 3;
    header.reserve = 0;
    header.offset = 54;
    header.header_size = 40;
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bpp = 24;
    header.compression = 0;
    header.bitmap_size = width * height * 3;
    header.hres = 0;
    header.vres = 0;
    header.used = 0;
    header.important = 0;

    // open the output file to write
    FILE *output = fopen(output_name, "wb");
    if (!output) {
        perror("fopen");
        return -1;
    }

    // write the header
    fwrite(&header, sizeof(sBmpHeader), 1, output);

    // write the pixels
    for (int i = 0; i < height; i++) {
        fwrite(pixels[i], sizeof(sPixel), width, output);
    }

    // exit
    return 0;
}
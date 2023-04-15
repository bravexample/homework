#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

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
} __attribute__ ((__packed__)) BMP_HEADER;

int main(void) {
    FILE* file = fopen( "maldives.bmp", "rb" );
    if (!file) {
        perror("Error: ");
        return -1;
    }

    BMP_HEADER header;
    fread( &header, sizeof( header ), 1, file );

    uint8_t *pPixels = NULL;
    pPixels = malloc( header.bitmap_size );
    fread( pPixels, header.bitmap_size, 1, file );

    fclose( file );

    file = fopen( "test.bmp", "wb" );
    if (!file) {
        perror("Error: ");
        return -1;
    }

    fwrite(&header, sizeof(header), 1, file);
    fwrite(pPixels, header.bitmap_size, 1, file);

    fclose(file);

    return 0;
}
// A program to turn a txt file to MIDI file

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "midi.h"

// Some constants
#define MAX_PATH_LEN 4096
#define MAX_INSTRUMENT_NAME_LEN 64

// VLV
void WriteVarLen(int32_t value, FILE *outfile) {
    int32_t buffer;
    buffer = value & 0x7f;
    while((value >>= 7) > 0)
    {
        buffer <<= 8;
        buffer |= 0x80;
        buffer += (value &0x7f);
    }

    while (1)
    {
        putc(buffer,outfile);
        if(buffer & 0x80)
            buffer >>= 8;
        else
            break;
    }
}

// Main
int32_t main(void) {
    // Display the menu
    printf("Welcome to Cool Sound Infinity Exporter!\n" \
           "Please enter input and output file name.\n" \
           "Input file name: ");
    
    // Get the path of file
    uint8_t input_file[MAX_PATH_LEN];
    if (!fgets(input_file, MAX_PATH_LEN, stdin)) {
        perror("fgets");
        return 1;
    }
    // Remove the newline character
    input_file[strlen(input_file) - 1] = '\0';

    // Get the output file name
    printf("Output file name: ");
    uint8_t output_file[MAX_PATH_LEN];
    if (!fgets(output_file, MAX_PATH_LEN, stdin)) {
        perror("fgets");
        return 1;
    }
    // Remove the newline character
    output_file[strlen(output_file) - 1] = '\0';

    // Open the input file with mmap
    int32_t input_fd = open(input_file, O_RDONLY);
    if (input_fd < 0) {
        perror("open");
        return 1;
    }
    struct stat input_stat;
    if (fstat(input_fd, &input_stat) < 0) {
        perror("fstat");
        return 1;
    }
    uint8_t *input_mmap = mmap(NULL, input_stat.st_size, PROT_READ, MAP_PRIVATE, input_fd, 0);
    if (input_mmap == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Open the output file
    FILE *output_fp = fopen(output_file, "wb");
    if (!output_fp) {
        perror("fopen");
        return 1;
    }

    // Create the header chunk
    sMIDIHeader header_chunk;
    header_chunk.chunk_id[0] = 'M';
    header_chunk.chunk_id[1] = 'T';
    header_chunk.chunk_id[2] = 'h';
    header_chunk.chunk_id[3] = 'd';
    header_chunk.chunk_size = 6;
    header_chunk.format_type = 1;

    // Get the number of tracks
    header_chunk.track_count = 0;
    for (uint32_t i = 0; i < input_stat.st_size; i++) {
        if (input_mmap[i] == '[')
            header_chunk.track_count++;
    }

    // Set the time division
    header_chunk.time_division = 480;

    // Write the header chunk use big endian
    {
        // Write the chunk id
        fwrite(header_chunk.chunk_id, sizeof(uint8_t), 4, output_fp);
        // Write the chunk size
        uint8_t chunk_size[4];
        chunk_size[0] = (header_chunk.chunk_size >> 24) & 0xFF;
        chunk_size[1] = (header_chunk.chunk_size >> 16) & 0xFF;
        chunk_size[2] = (header_chunk.chunk_size >> 8) & 0xFF;
        chunk_size[3] = header_chunk.chunk_size & 0xFF;
        fwrite(chunk_size, sizeof(uint8_t), 4, output_fp);
        // Write the format type
        uint8_t format_type[2];
        format_type[0] = (header_chunk.format_type >> 8) & 0xFF;
        format_type[1] = header_chunk.format_type & 0xFF;
        fwrite(format_type, sizeof(uint8_t), 2, output_fp);
        // Write the track count
        uint8_t track_count[2];
        track_count[0] = (header_chunk.track_count >> 8) & 0xFF;
        track_count[1] = header_chunk.track_count & 0xFF;
        fwrite(track_count, sizeof(uint8_t), 2, output_fp);
        // Write the time division
        uint8_t time_division[2];
        time_division[0] = (header_chunk.time_division >> 8) & 0xFF;
        time_division[1] = header_chunk.time_division & 0xFF;
        fwrite(time_division, sizeof(uint8_t), 2, output_fp);
    }

    // The track chunk id
    uint8_t track_chunk_id[4] = {'M', 'T', 'r', 'k'};
    // Channel
    uint8_t channel[] = {0x00, 0xC0, 0x00};
    // Variable for the input file
    uint32_t i = 0;
    // Loop for each track
    while (i < input_stat.st_size) {
        // Variable for the track size
        int32_t track_size = 0;
        
        // Get the instrument name
        // Which is the first line of the track
        // looks like [InstrumentName]
        uint8_t instrument_name[MAX_INSTRUMENT_NAME_LEN] = {0};
        for (uint32_t j = 0; input_mmap[i] != '\n'; i++)
            if (input_mmap[i] != '[' && input_mmap[i] != ']') {
                instrument_name[j] = input_mmap[i];
                j++;
            }
        // Skip the newline character
        i++;

        // Setup instrument
        channel[2] = 0;
        for (; channel[2] < MAX_INSTRUMENTS; channel[2]++)
            if (!strcmp(instrument_name, instruments[channel[2]]))
                break;

        // Loop for each note
        // 1 to 7 means middle C to B
        // 0 means rest
        // - means double the length
        // . means one and a half the length
        // ; means half the length
        // ' means octave up
        // , means octave down
        // [ means start of the next track
        // ignore other characters
        uint8_t last_note = 129;
        uint8_t last_time = 0;
        while (input_mmap[i] != '[' && i < input_stat.st_size) {
            switch (input_mmap[i]) {
            case '1':
                if (last_note < 129) {
                    // Write the note
                }
                
                last_note = 60;
                last_time
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '0':
            case '-':
            case '.':
            case ';':
            case '\'':
            case ',':
            default:
            }
        }
    }

    // Exit
    return 0;
}
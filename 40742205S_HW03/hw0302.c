#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZIP_LOCAL_HEADER_SIGNATURE 0x04034b50
#define ZIP_CENTRAL_HEADER_SIGNATURE 0x02014b50
#define ZIP_END_OF_CENTRAL_DIR_SIGNATURE 0x06054b50

struct zip_local_header {
    uint32_t signature;
    uint16_t version_needed;
    uint16_t general_bit_flag;
    uint16_t compression_method;
    uint16_t file_mod_time;
    uint16_t file_mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t file_name_length;
    uint16_t extra_field_length;
};

struct zip_central_header {
    uint32_t signature;
    uint16_t version_made_by;
    uint16_t version_needed;
    uint16_t general_bit_flag;
    uint16_t compression_method;
    uint16_t file_mod_time;
    uint16_t file_mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t file_name_length;
    uint16_t extra_field_length;
    uint16_t file_comment_length;
    uint16_t disk_number_start;
    uint16_t internal_file_attributes;
    uint32_t external_file_attributes;
    uint32_t relative_offset;
};

struct zip_end_of_central_dir {
    uint32_t signature;
    uint16_t disk_number;
    uint16_t central_dir_disk;
    uint16_t num_entries_on_disk;
    uint16_t num_entries_total;
    uint32_t central_dir_size;
    uint32_t central_dir_offset;
    uint16_t comment_length;
};

void print_directory(const char* zip_file_path);

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <zip-file>\n", argv[0]);
        return 1;
    }

    print_directory(argv[1]);

    return 0;
}

void print_directory(const char* zip_file_path) {
    FILE* zip_file = fopen(zip_file_path, "rb");
    if (!zip_file) {
        printf("Error: could not open zip file %s: %s\n", zip_file_path, strerror(errno));
        return;
    }

    // Find the end of central directory record
    fseek(zip_file, 0, SEEK_END);
    long file_size = ftell(zip_file);
    if (file_size < sizeof(struct zip_end_of_central_dir)) {
        printf("Error: invalid zip file %s\n", zip_file_path);
        fclose(zip_file);
        return;
    }

    struct zip_end_of_central_dir eocd;
    long offset = file_size - sizeof(struct zip_end_of_central_dir);
    while (offset >= 0) {
        fseek(zip_file, offset, SEEK_SET);
        fread(&eocd, sizeof(struct zip_end_of_central_dir), 1, zip_file);
        if (eocd.signature == ZIP_END_OF_CENTRAL_DIR_SIGNATURE) {
            break;
        }
        offset--;
    }
}
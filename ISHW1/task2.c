#include <stdio.h>
#include <stdlib.h>

#define KEYSIZE 16

void convert_time(const char *src, size_t *time) {
    for (size_t i = 0; src[i]; i++) {
        *time *= 10;
        *time += src[i] - '0';
    }
}

void convert_hex(const char *hex, char *result) {
    for (size_t i = 0, j = 0; hex[i]; i++, j++) {
        if (hex[i] >= 'a' && hex[i] <= 'f')
            result[j] = hex[i] - 'W';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            result[j] = hex[i] - '7';
        else
            result[j] = hex[i] - '0';
        
        result[j] <<= 4;
        i++;

        if (hex[i] >= 'a' && hex[i] <= 'f')
            result[j] += hex[i] - 'W';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            result[j] = hex[i] - '7';
        else
            result[j] += hex[i] - '0';
    }
}

int main(void) {
    char *plaintext_hex = "255044462d312e350a25d0d4c5d80a34";
    char plaintext[KEYSIZE] = {0};
    convert_hex(plaintext_hex, plaintext);

    char *initvector_hex = "09080706050403020100A2B2C2D2E2F2";
    char initvector[KEYSIZE] = {0};
    convert_hex(initvector_hex, initvector);

    char *ciphertext_hex = "d06bf9d0dab8e8ef880660d2af65aa82";
    char ciphertext[KEYSIZE] = {0};
    convert_hex(ciphertext_hex, ciphertext);

    FILE *file = fopen("timestamp", "rb");
    if (!file)
        return 0;

    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    char *time_str = calloc(len + 1, sizeof(char));
    rewind(file);
    size_t check = fread(time_str, len, 1, file);
    if (!check)
        return 0;
    fclose(file);

    size_t time = 0;
    convert_time(time_str, &time);
    free(time_str);

    char key[KEYSIZE] = {0};
    char result[KEYSIZE];
    for (size_t j = 0; j < 7200; j++) {
        srand(time - j);
        size_t i = 0;
        for (; i< KEYSIZE; i++) {
            result[i] = initvector[i] ^ plaintext[i];
            key[i] = rand()%256;
            result[i] ^= key[i];
            if ((result[i] ^ key[i]))
                break;
        }

        if (i == KEYSIZE) {
            for (i = 0; i< KEYSIZE; i++)
                printf("%.2x", result[i]);

            printf("\n");
            break;
        }
    }

    return 1;
}
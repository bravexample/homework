#include <stdio.h>

int main() {
    FILE *fp = fopen("abc", "wb");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    long long temp = -1;
    for (int i = 0; i < 10 ; i++) {
        fwrite(&temp, sizeof(long long), 1, fp);
    }

    return 0;
}
// hw0101.c
#include "mystring.h"
#include <stdio.h>

int main() {
    char str1[] = "Hello world";
    char str2[] = "banana";
    char str3[] = "This is a string";
    char *result;

    // Test mystrchr
    result = mystrchr(str1, 'o');
    printf("mystrchr: %s\n", result);

    // Test mystrrchr
    result = mystrrchr(str1, 'l');
    printf("mystrrchr: %s\n", result);

    // Test mystrspn
    size_t len = mystrspn(str2, "an");
    printf("mystrspn: %lu\n", len);

    // Test mystrcspn
    len = mystrcspn(str2, "n");
    printf("mystrcspn: %lu\n", len);

    // Test mystrpbrk
    result = mystrpbrk(str2, "na");
    printf("mystrpbrk: %s\n", result);

    // Test mystrstr
    result = mystrstr(str3, "is");
    printf("mystrstr: %s\n", result);

    // Test mystrtok
    char *token = mystrtok(str3, " ");
    while(token != NULL) {
        printf("mystrtok: %s\n", token);
        token = mystrtok(NULL, " ");
    }

    return 0;
}

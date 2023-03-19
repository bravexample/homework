#include <stdio.h>
#include "mystring.h"

char *key_compare(const char *source, const char *key) {
    const char *pos = source, *ret = NULL;
    for (;;) {
        ret = mystrpbrk(pos, "\"");
        if (!ret)
            break;
        
        pos = ret + 1;
        if (*pos == *key) {
            int i = 1;
            pos++;
            for (; key[i]; i++, pos++) {
                if (*pos != key[i])
                    break;
            }
            
            if (!key[i] && *pos == '\"') {
                return (char *)pos + 1;
            }
        }

        ret = mystrpbrk(pos, ":");
        if (ret[2] == '{') {
            int layer = 0;
            do {
                ret = mystrpbrk(ret, "{}");
                if (*ret == '{')
                    layer++;
                else if (layer && *ret == '}')
                    layer--;
                
                ret++;
            } while (layer);
        }

        ret = mystrpbrk(ret, ",");
        if (!ret)
            break;
        pos = ret + 1;
    }

    return NULL;
}

int main(void) {
    char inputs[8200] = {0};
    puts("Please enter the JSON string:");
    for (int i = 0, j = fgetc(stdin);
         i < 8193 && j != '\n';
         i++, j = fgetc(stdin))
         inputs[i] = j;

    int choice = 0, dump = 0;
    char *position = NULL;
    for (;;) {
        printf("Choice (0:Exit ,1:Get) : ");
        choice = fgetc(stdin) - '0';
        if (!choice) {
            puts("Bye");
            break;
        }

        while ((dump = fgetc(stdin)) != '\n');

        printf("Key: ");
        char key[8200] = {0};
        for (int i = 0, j = fgetc(stdin);
             i < 8193 && j != '\n';
             i++, j = fgetc(stdin))
             key[i] = j;
        
        position = inputs;
        for (char *subKey = mystrtok(key, "."); subKey; subKey = mystrtok(NULL, "."))
            if (!(position = key_compare(position, subKey)))
                break;

        if (position) {
            printf("Value: ");
            position += 2;
            if (*position == '\"') {
                position++;
                for (; *position != '\"'; position++)
                    printf("%c", *position);
                
                puts("");
            } else if (*position == '{') {
                int layer = 0;
                do {
                    printf("%c", *position);
                    if (*position == '{')
                        layer++;
                    else if (*position == '}')
                        layer--;

                    position++;
                } while (layer);

                puts("");
            } else {
                for (; *position != ','; position++)
                    printf("%c", *position);
                
                puts("");
            }
        } else {
            puts("Not Found.");
        }
    }

    return 1;
}
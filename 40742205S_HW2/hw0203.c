#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 2048

typedef struct {
    char id[16];
    char chapter[8];
    char verse[8];
    char text[STR_MAX];
    void *next;
} LINK_LIST;

int main(void) {
    char string[STR_MAX] = {0};
    printf("Please enter the search target: ");
    fgets(string, STR_MAX, stdin);

    int i = 0;
    for (; string[i] != '\n'; i++) {
        if (string[i] >= 'A' && string[i] <= 'Z')
            string[i] ^= ' ';
    }
    string[i] = '\0';

    FILE *file = fopen("bible.txt", "rb");
    if (!file) {
        perror("Error: ");
        return -1;
    }

    LINK_LIST *queue = (LINK_LIST *)calloc(1, sizeof(LINK_LIST));
    char *text_start = NULL;
    char buffer[STR_MAX] = {0};
    char to_compare[STR_MAX] = {0};
    char temp = fgetc(file);
    int found_times = 0;
    for(LINK_LIST *now = queue;;) {
        char *check = fgets(buffer, STR_MAX, file);
        if (!check)
            break;

        for (int j = 0; buffer[j] != '}'; j++)
            to_compare[j] = (buffer[j] >= 'A' && buffer[j] <= 'Z') ? buffer[j] ^ ' ' : buffer[j];
        
        text_start = strstr(to_compare, "\"text\":\"");
        text_start += 8;

        if (strstr(to_compare, string)) {
            found_times++;

            text_start = strstr(buffer, "\"text\":\"");
            text_start += 8;
            for (int j = 0; text_start[j] != '\"'; j++)
                now->text[j] = text_start[j];

            text_start = strstr(buffer, "\"chapter\":");
            text_start += 10;
            for (int j = 0; text_start[j] != ','; j++)
                now->chapter[j] = text_start[j];
            
            text_start = strstr(buffer, "\"verse\":");
            text_start += 8;
            for (int j = 0; text_start[j] != ','; j++)
                now->verse[j] = text_start[j];
            
            text_start = strstr(buffer, "\"book_id\":\"");
            text_start += 11;
            for (int j = 0; text_start[j] != '\"'; j++)
                now->id[j] = text_start[j];
            
            now->next = (LINK_LIST *)calloc(1, sizeof(LINK_LIST));
            now = now->next;
        }
    }

    printf("Found %d time(s)\n", found_times);
    i = 1;
    for (LINK_LIST *now = queue; now->next; now = now->next, i++)
        printf("%d. %s %s:%s %s\n", i, now->id, now->chapter, now->verse, now->text);
    
    return 0;
}
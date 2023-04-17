#include <stdio.h>

typedef struct {
    signed int index : 24;
    signed int value : 8;
} CELL;

int main(void) {
    int region, action, i, j;
    scanf("%d %d", &region, &action);

    CELL progress[region + 1];
    int last, temp;
    for (i = 0, last = 0; i < region; i++) {
        scanf("%d", &temp);
        if (temp) {
            progress[last].index = i;
            progress[last].value = temp;
            last++;
        }
    }

    progress[last].value = 0;
    last--;

    int start, end, explore;
    for (i = 0; i < action; i++) {
        scanf("%d %d %d", &start, &end, &explore);
        if (explore) {
            for (j = 0; progress[j].value > 0; j++) {
                if (progress[j].index >= start && progress[j].index <= end) {
                    progress[j].value -= explore;

                    if (progress[j].value <= 0) {
                        progress[j] = progress[last];
                        progress[last].value = 0;
                        last--;
                        j--;
                    }
                }
            }

            if (last < 0) {
                printf("%d", i + 1);
                return 0;
            }
        }
    }
    
    printf("-1");
    return 0;
}
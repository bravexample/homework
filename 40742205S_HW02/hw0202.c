#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define PATH_MAX 4096
#define FILE_MAX 4096

typedef struct {
    char path[PATH_MAX];
    struct dirent child[FILE_MAX];
    DIR *dp;
    void *next;
} LINK_LIST;

int main(void) {
    LINK_LIST *queue = (LINK_LIST *)calloc(1, sizeof(LINK_LIST));

    strcpy(queue->path, ".");
    queue->dp = opendir(queue->path);

    struct dirent *dirp;
    for (LINK_LIST *i = queue, *j = queue, *k = NULL; i;) {
        printf("\033[31m%s\033[37m:\n", i->path);

        while ((dirp = readdir(i->dp))) {
            if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
                continue;

            struct dirent dir = *dirp, temp;
            int l = 0;
            for (; i->child[l].d_type; l++)
                if (strcmp(dir.d_name, i->child[l].d_name) < 0) {
                    temp = i->child[l];
                    i->child[l] = dir;
                    dir = temp;
                }
            
            i->child[l] = dir;
        }

        for (int l = 0; i->child[l].d_type; l++) {
            if (i->child[l].d_type == DT_DIR) {
                j->next = (LINK_LIST *)calloc(1, sizeof(LINK_LIST));
                j = j->next;
                sprintf(j->path, "%s/%s", i->path, i->child[l].d_name);
                j->dp = opendir(j->path);
                j->next = NULL;

                printf("\033[34m%s ", i->child[l].d_name);
            }
            else
                printf("\033[37m%s ", i->child[l].d_name);
        }

        printf("\n\n");

        closedir(i->dp);
        k = i;
        i = i->next;
        free(k);
    }

    return 0;
}
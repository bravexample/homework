#include <stdint.h>
#include <stdlib.h>

int32_t strinsert(char **ppResult, const char *pStr1, int32_t location, const char *pStr2) {
    if (!ppResult || (!pStr1 && !pStr2))
        return -1;

    if (!pStr1)
        pStr1 = "";
    
    if (!pStr2)
        pStr2 = "";
    
    size_t len = 0;
    while (pStr1[len])
        len++;
    
    if (location > len)
        return -1;
    
    for (size_t i = 0; pStr2[i]; i++)
        len++;
    
    *ppResult = malloc((len + 1) * sizeof(char));
    for (size_t i = 0, j = 0; i <= len; i++, j++) {
        if (i == location)
            for (size_t k = 0; pStr2[k]; i++, k++)
                (*ppResult)[i] = pStr2[k];

        (*ppResult)[i] = pStr1[j];
    }

    return 0;
}
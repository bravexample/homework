#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _sAbacus{
    uint8_t number;
    uint8_t *pUpperRod;
    uint8_t *pLowerRod;
} sAbacus;

sAbacus *abacus_init(void) {
    return calloc(1, sizeof(sAbacus));
}

void abacus_free(sAbacus *abacus) {
    if (!abacus)
        return;

    if (abacus->pUpperRod)
        free(abacus->pUpperRod);

    if (abacus->pLowerRod)
        free(abacus->pLowerRod);
    
    free(abacus);
}

int32_t abacus_set(sAbacus *pA, char *pStr) {
    if (!pA || !pStr)
        return -1;
    
    size_t len = 0;
    while (pStr[len]) {
        if (pStr[len] < '0' || pStr[len] > '9')
            return -1;
        
        len++;
    }
    
    if (len > 255 || !len)
        return -1;

    pA->number = len;

    if (pA->pUpperRod)
        free(pA->pUpperRod);
    pA->pUpperRod = malloc(len * sizeof(char));

    if (pA->pLowerRod)
        free(pA->pLowerRod);
    pA->pLowerRod = malloc(len * sizeof(char));

    for (size_t i = 0; pStr[i]; i++) {
        char temp = pStr[i] - '0';
        pA->pUpperRod[i] = temp / 5;
        pA->pLowerRod[i] = temp % 5;
    }

    return 0;
}

int32_t abacus_add(sAbacus *pA, sAbacus b, sAbacus c) {
    if (!pA)
        return -1;

    if (b.number && (!b.pUpperRod || !b.pLowerRod))
        return -1;
    
    if (c.number && (!c.pUpperRod || !c.pLowerRod))
        return -1;

    sAbacus *result = abacus_init();

    result->number    = b.number > c.number ? b.number : c.number;
    result->pUpperRod = malloc(result->number * sizeof(char));
    result->pLowerRod = malloc(result->number * sizeof(char));

    char temp = 0, over = 0;
    for (size_t i = b.number, j = c.number, k = result->number; i || j;) {
        temp = 0;
        if (i) {
            i--;
            temp += b.pUpperRod[i] * 5;
            temp += b.pLowerRod[i];
        }
        
        if (j) {
            j--;
            temp += c.pUpperRod[j] * 5;
            temp += c.pLowerRod[j];
        }
        
        temp += over;
        over = 0;
        if (temp > 9) {
            over = 1;
            temp -= 10;
        }

        k--;
        result->pUpperRod[k] = temp / 5;
        result->pLowerRod[k] = temp % 5;
    }

    if ((int )result->number + (int )over > 255)
        return -1;

    pA->number = result->number + over;
    
    if (pA->pUpperRod)
        free(pA->pUpperRod);
    pA->pUpperRod = malloc(pA->number * sizeof(char));

    if (pA->pLowerRod)
        free(pA->pLowerRod);
    pA->pLowerRod = malloc(pA->number * sizeof(char));
    
    pA->pUpperRod[0] = 0;
    pA->pLowerRod[0] = 1;
    for (int i = 0; i < result->number; i++) {
        pA->pUpperRod[i + over] = result->pUpperRod[i];
        pA->pLowerRod[i + over] = result->pLowerRod[i];
    }

    return 0;
}

int32_t abacus_del(sAbacus *pA, sAbacus b, sAbacus c) {
    if (!pA || b.number < c.number)
        return -1;
    
    if (b.number && (!b.pUpperRod || !b.pLowerRod))
        return -1;
    
    if (c.number && (!c.pUpperRod || !c.pLowerRod))
        return -1;
    
    sAbacus *result = abacus_init();

    result->number    = b.number;
    result->pUpperRod = malloc(result->number * sizeof(char));
    result->pLowerRod = malloc(result->number * sizeof(char));

    int temp = 0, less = 0;
    for (size_t i = b.number, j = c.number; i || j;) {
        temp = 0;
        if (i) {
            i--;
            temp += b.pUpperRod[i] * 5;
            temp += b.pLowerRod[i];
        }

        if (j) {
            j--;
            temp -= c.pUpperRod[j] * 5;
            temp -= c.pLowerRod[j];
        }

        temp -= less;
        less = 0;
        if (temp < 0) {
            less = 1;
            temp += 10;
        }

        result->pUpperRod[i] = temp / 5;
        result->pLowerRod[i] = temp % 5;
    }

    if (less)
        return -1;
    
    pA->number = result->number;

    if (pA->pUpperRod)
        free(pA->pUpperRod);
    pA->pUpperRod = malloc(pA->number * sizeof(char));

    if (pA->pLowerRod)
        free(pA->pLowerRod);
    pA->pLowerRod = malloc(pA->number * sizeof(char));

    for (size_t i = 0; i < pA->number; i++) {
        pA->pUpperRod[i] = result->pUpperRod[i];
        pA->pLowerRod[i] = result->pLowerRod[i];
    }

    return 0;
}

int32_t abacus_print(sAbacus a) {
    if (!a.number) {
        printf("*\n\n-\n\n*\n*\n*\n*\n");
        return 0;
    }

    if (!a.pUpperRod || !a.pLowerRod)
        return -1;
    
    size_t start = 0;
    for (; start < a.number; start++)
        if (a.pUpperRod[start] || a.pLowerRod[start])
            break;
    
    if (start == a.number){
        printf("*\n\n-\n\n*\n*\n*\n*\n");
        return 0;
    }

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = start; j < a.number; j++)
            if (a.pUpperRod[j] == i)
                printf("*");
            else
                printf(" ");
        
        printf("\n");
    }

    for (size_t j = start; j < a.number; j++)
        printf("-");

    printf("\n");

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = start; j < a.number; j++)
            if (a.pLowerRod[j] == i)
                printf(" ");
            else
                printf("*");
        
        printf("\n");
    }

    return 0;
}
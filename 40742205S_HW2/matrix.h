#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _sMatrix {
    int32_t row;
    int32_t column;
    int32_t **data;
} sMatrix;

sMatrix *matrix_init(uint8_t m, uint8_t n) {
    if (!m || !n)
        return NULL;

    sMatrix *matrix = (sMatrix *)malloc(sizeof(sMatrix));

    matrix->row = m;
    matrix->column = n;

    matrix->data = (int32_t **)malloc(m * sizeof(int32_t *));
    for (int32_t i = 0; i < m; i++)
        matrix->data[i] = (int32_t *)calloc(n, sizeof(int32_t));
    
    return matrix;
}

int32_t matrix_free(sMatrix *pA) {
    if (!pA)
        return -1;
    
    for (int32_t i = 0; i < pA->row; i++)
        if (pA->data[i])
            free(pA->data[i]);
    
    free(pA->data);

    return 0;
}

int32_t matrix_set(sMatrix *pM, uint8_t m, uint8_t n, int32_t value) {
    if (m == 256 || n == 256)
        return -1;
    
    if (m > pM->row - 1 || n > pM->column - 1)
        return -1;
    
    for (int32_t i = 0; i <= m; i++)
        for (int32_t j = 0; j <= n; j++)
            pM->data[i][j] = value;

    return 0;
}

void matrix_print(const sMatrix *pM) {
    if (!pM)
        return;

    for (int32_t i = 0; i < pM->row; i++) {
        printf("%d", pM->data[i][0]);

        for (int32_t j = 1; j < pM->column; j++)
            printf(" %d", pM->data[i][j]);
        
        printf("\n");
    }
}

int32_t matrix_add(sMatrix *pA, const sMatrix *pB, const sMatrix *pC) {
    if (!pB || !pC || (pB->row != pC->row) || (pB->column != pC->column))
        return -1;
    
    for (int32_t i = 0; i < pA->row; i++)
        for (int32_t j = 0; j < pA->column; j++)
            pA->data[i][j] = pB->data[i][j] + pC->data[i][j];
    
    return 0;
}

int32_t matrix_multiply(sMatrix *pA, const sMatrix *pB, const sMatrix *pC) {
    if (!pB || !pC || (pB->column != pC->row))
        return -1;
    
    for (int32_t i = 0; i < pA->row; i++)
        for (int32_t j = 0; j < pA->column; j++) {
            pA->data[i][j] = 0;
            for (int32_t k = 0; k < pC->column; k++)
                pA->data[i][j] += pB->data[i][k] * pC->data[k][j];
        }
            
    
    return 0;
}

int32_t matrix_transpose(sMatrix *pA) {
    if (!pA)
        return -1;

    sMatrix *matrix = matrix_init(pA->column, pA->row);

    for (int32_t i = 0; i < pA->row; i++)
        for (int32_t j = 0; j < pA->column; j++)
            matrix->data[j][i] = pA->data[i][j];

    int32_t **temp = pA->data;
    *pA = *matrix;
    matrix->data = temp;

    matrix_free(matrix);

    return 0;
}

int32_t matrix_det(const sMatrix *pA, int32_t *pAns) {
    if (!pA || !pAns || !pA->row || !pA->column)
        return -1;

    if (pA->row != pA->column)
        return -1;
    
    if (pA->row == 1) {
        *pAns = pA->data[0][0];
        return 0;
    }

    *pAns = 0;

    for (int32_t i = 0, sign = 1; i < pA->column; i++, sign *= -1) {
        sMatrix *matrix = matrix_init(pA->row - 1, pA->column - 1);

        for (int32_t j = 1; j < pA->row; j++)
            for (int32_t k = 0, l = 0; k < pA->column; k++) {
                if (k == i)
                    continue;
                
                matrix->data[j - 1][l] = pA->data[j][k];
                l++;
            }
        
        int32_t temp;
        matrix_det(matrix, &temp);
        *pAns += sign * pA->data[0][i] * temp;

        matrix_free(matrix);
    }

    return 0;
}
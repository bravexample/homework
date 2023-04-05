#include "matrix.h"

int main(void) {
    sMatrix *pA = matrix_init(3, 3);

    int32_t array[] = {1, 1, 0, 0, 1, 1, 0, 1, 1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pA->data[i][j] = array[i * 3 + j];
        }
    }

    matrix_print(pA);
    matrix_transpose(pA);
    matrix_print(pA);

    return 0;
}
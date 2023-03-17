// hw0103.c
#include "abacus.h"
#include <stdio.h>

int main() {
    // Initialize abacus, abacus2, abacus3
    sAbacus *abacus = abacus_init();
    sAbacus *abacus2 = abacus_init();
    sAbacus *abacus3 = abacus_init();

    // Set the values of abacus and abacus2 to "1234" and "5678"
    if(abacus_set(abacus, "1234") != 0) {
        printf("Error: Set operation failed\n");
        return -1;
    }
    if(abacus_set(abacus2, "5678") != 0) {
        printf("Error: Set operation failed\n");
        return -1;
    }

    // Add abacus and abacus2, store result in abacus3
    if(abacus_add(abacus3, *abacus, *abacus2) != 0) {
        printf("Error: Add operation failed\n");
        return -1;
    }

    // Print abacus3
    if(abacus_print(*abacus3) != 0) {
        printf("Error: Print operation failed\n");
        return -1;
    }

    // Subtract abacus from abacus2, store result in abacus3
    if(abacus_del(abacus3, *abacus2, *abacus) != 0) {
        printf("Error: Del operation failed\n");
        return -1;
    }

    // Print abacus3
    if(abacus_print(*abacus3) != 0) {
        printf("Error: Print operation failed\n");
        return -1;
    }

    // Free memory
    abacus_free(abacus);
    abacus_free(abacus2);
    abacus_free(abacus3);

    return 0;
}

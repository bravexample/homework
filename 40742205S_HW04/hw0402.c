// a program to test macros.h

// includes
#include <stdio.h>
#include "macros.h"

// main
int main(void) {
    // test BIT(x)
    printf("BIT(5) = %d\n", BIT(5));
    printf("BIT(6) = %d\n", BIT(6));
    printf("BIT(7) = %d\n", BIT(7));

    int x;

    // test SETBIT(x,p)
    for (int i = 0; i < 3; i++) {
        x = 0;
        printf("SETBIT(x,%d) = %d\n", i, SETBIT(x,i));
    }

    // test CLEARBIT(x,p)
    for (int i = 0; i < 3; i++) {
        x = 1;
        printf("CLEARBIT(x,%d) = %d\n", i, CLEARBIT(x,i));
    }

    // test GETBIT(x,p)
    x = 1;
    for (int i = 0; i < 3; i++) {
        printf("GETBIT(x,%d) = %d\n", i, GETBIT(x,i));
    }

    // test TOGGLEBIT(x,p)
    for (int i = 0; i < 3; i++) {
        x = -1;
        printf("TOGGLEBIT(x,%d) = %d\n", i, TOGGLEBIT(x,i));
    }

    // test RANGE(i,x,y)
    for RANGE(i,20,10) {
        printf("i = %ld\n", i);
    }

    // test FOREACH(i,A)
    int A[] = {1,2,3,4,5};
    FOREACH(i,A) {
        printf("i = %ld\n", i);
        i -= 5;
    }
    FOREACH(i,A) {
        printf("i = %ld\n", i);
    }

    // exit
    return 0;
}
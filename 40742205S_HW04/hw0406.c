#include <stdio.h>
#define Peval(cmd) printf( #cmd ": %g\n", cmd )

int main()
{
    double *plist = (double[]){1, 2, 3};
    double list[] = {1, 2, 3};
    Peval( sizeof( plist ) / ( sizeof( double ) + 0.0 ) );
    Peval( sizeof( list ) / ( sizeof( double ) + 0.0 ) );
    return 0;
}

// #define PRINT_INT(var) printf("the value of "#var" is: %d\n", var)

// #include <stdio.h>

// int main() {
//     int temp = 0;
//     PRINT_INT(temp);

//     return 0;
// }
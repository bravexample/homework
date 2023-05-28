// a header includes macros for bit operations and other useful stuff

#ifndef MACROS_H
#define MACROS_H

#include <stdint.h>

#define BIT(x) (1 << x)
#define SETBIT(x,p) (x |= BIT(p))
#define CLEARBIT(x,p) (x &= ~BIT(p))
#define GETBIT(x,p) ((x >> p) & 1)
#define TOGGLEBIT(x,p) (x ^= BIT(p))
#define RANGE(i,y,x) (int64_t i = y, ii = 0, iii = (y < x ? x - y : y - x) + 1; ii < iii; i += (y < x ? 1 : -1), ii++)
#define FOREACH(i,A) for (uint64_t ii = 0, i = A[ii], iii = sizeof(A) / sizeof(A[0]); ii < iii; A[ii] = i, ii++, i = (ii < iii ? A[ii] : 0))

#endif
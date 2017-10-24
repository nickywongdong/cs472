#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "concat.c"


#define F64_EXP_MAX 2048 //2^11

#define F64_EXP_MASK 0x7FF0000000000000 //exponent masked
#define F64_EXP_SHIFT   52      //shift 52 times to the right
#define F64_GET_EXP(fp)

#define F64_MANT_MASK   8388608 //2^23
#define F64_MANT_SHIFT  
#define F64_GET_MANT_HIGH(fp)
#define F64_GET_MANT_LOW(fp)

#define F64_EXP_BIAS    1023
#define F64_SET_EXP

double
frexp(value, eptr)
    double value;
    int *eptr;
{
    union {
        double v;
        double s;
    } u;

    if (value) {
        /*
         * Fractions in [0.5..1.0) have an exponent of 2^-1.
         * Leave Inf and NaN alone, however.
         * WHAT ABOUT DENORMS?
         */
        u.v = value;
        if (u.s.dbl_exp != DBL_EXP_INFNAN) {
            *eptr = u.s.dbl_exp - (DBL_EXP_BIAS - 1);
            u.s.dbl_exp = DBL_EXP_BIAS - 1;
        }
        return (u.v);
    } else {
        *eptr = 0;
        return (0.0);
    }
}
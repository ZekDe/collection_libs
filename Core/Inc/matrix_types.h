#ifndef MATRIX_TYPES_H
#define MATRIX_TYPES_H

#include <stdint.h>
#include <float.h>
#include <stdbool.h>

typedef float real_t;
typedef _Bool boolean_t;

#define CREAL_T 1


#define CREATE_EMPTY_MATRIX(A, row, col)\
creal_t data##A[row * col];\
int32_t size##A[2] = {row, col};\
matrix_t A={\
    .size = size##A,\
    .data = data##A,\
};\

#define CREATE_MATRIX(A, row, col) \
int32_t size##A[2] = {row, col};\
matrix_t A={\
    .size = size##A,\
    .data = data##A,\
};\

typedef struct
{
    real_t re;
    real_t im;
}creal_t;

typedef struct
{
#if CREAL_T
    creal_t *data;
#else
    real_t *data;
#endif
    int32_t *size;
}matrix_t;


#endif // MATRIX_TYPES_H

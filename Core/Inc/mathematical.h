#ifndef MATHEMATICAL_H
#define MATHEMATICAL_H

#include <stdint.h>
#include <float.h>

#define SUPPORT_COMPLEX_NUMBER  1

#define CREATE_EMPTY_MATRIX(A, row, col)\
creal_t data##A[row * col];\
int32_t sizeof##A[2] = {row, col};\
matrix_t A={\
    .size = sizeof##A,\
    .data = data##A,\
};\

#define CREATE_MATRIX(A, row, col) \
int32_t sizeof##A[2] = {row, col};\
matrix_t A={\
    .size = sizeof##A,\
    .data = data##A,\
};\


typedef float real_t;

typedef struct
{
    real_t re;
    real_t im;
}creal_t;

typedef struct
{
    creal_t *data;
    int32_t *size;
}matrix_t;

void printMatrix(const matrix_t *pS);
void alignMatrix(creal_t *s, int32_t row, int32_t col);
void transpose(const matrix_t *A, matrix_t *B);
void setColons(matrix_t *pfVector, float fBegin, float fInterval, float fEnd);
void setLinSpace(const creal_t begin, const creal_t endpoint, float count, matrix_t *X);
void multiply(const matrix_t *A, const matrix_t *B, matrix_t *C);


#endif // MATHEMATICAL_H

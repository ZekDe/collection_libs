#ifndef MATHEMATICAL_H
#define MATHEMATICAL_H

#include <stdint.h>
#include <float.h>

#define SUPPORT_COMPLEX_NUMBER  1

#define CREATE_EMPTY_MATRIX(A, row, col)\
creal_t data##A[row * col] = {0};\
int sizeof##A[2] = {row, col};\
matrix_t A={\
    .size = sizeof##A,\
    .data = data##A,\
};\

#define CREATE_MATRIX_DATA(A, re_im, row, col) real_t data##A##re_im[row * col]

typedef float real_t;

typedef struct
{
    real_t re;
    real_t im;
}creal_t;

typedef struct
{
    creal_t *data;
    int *size;
}matrix_t;

void fillMatrixDataRe(creal_t *data, const real_t *dataRe, int size);
void fillMatrixDataIm(creal_t *data, const real_t *dataIm, int size);
void printMatrix(const matrix_t *pS);
void transpose(const matrix_t *A, matrix_t *B);
void setColons(matrix_t *pfVector, float fBegin, float fInterval, float fEnd);
void setLinSpace(const creal_t begin, const creal_t endpoint, float count, matrix_t *X);


#endif // MATHEMATICAL_H

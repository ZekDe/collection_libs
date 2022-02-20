#ifndef MATHEMATICAL_H
#define MATHEMATICAL_H

#include <stdint.h>
#include <float.h>

#define SUPPORT_COMPLEX_NUMBER  1

/**
 * \def CREATE_EMPTY_MATRIX
 * \brief
 * \example
 * CREATE_EMPTY_MATRIX(B, 3, 5);
 */
#define CREATE_EMPTY_MATRIX(A, row, col)\
creal_t data##A[row * col] = {0};\
int sizeof##A[2] = {row, col};\
matrix_t A={\
    .size = sizeof##A,\
    .data = data##A,\
};\

/**
 * \def CREATE_MATRIX
 * \brief
 * \example
creal_t dataA[]=
{
    {1.1, 0},{2.3, 0},{5.4, 0},
    {3.1, 0},{2.9, 0},{1.456, 0},
    {4.62, 0},{5.65, 0},{6.78, 0},
    {1.0, 0},{2.0, 0},{3.0, 3},
    {3.0, 0},{4.0, 0},{5.0, 0},
};
CREATE_MATRIX(A, 5, 3);
 *
 */
#define CREATE_MATRIX(A, row, col) \
int sizeof##A[2] = {row, col};\
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
    int *size;
}matrix_t;

void fillMatrixDataRe(creal_t *data, const real_t *dataRe, int size);
void fillMatrixDataIm(creal_t *data, const real_t *dataIm, int size);
void printMatrix(const matrix_t *pS);
void transpose(const matrix_t *A, matrix_t *B);
void setColons(matrix_t *pfVector, float fBegin, float fInterval, float fEnd);
void setLinSpace(const creal_t begin, const creal_t endpoint, float count, matrix_t *X);


#endif // MATHEMATICAL_H

#ifndef BASIC_MATRIX_OPERATIONS_H
#define BASIC_MATRIX_OPERATIONS_H

#include "matrix_types.h"

void printMatrix(const matrix_t *pS);
void transpose(const matrix_t *A, matrix_t *B);
void multiply(const matrix_t *A, const matrix_t *B, matrix_t *C);
#if CREAL_T
void alignMatrix(creal_t *s, int32_t row, int32_t col);
#else
void alignMatrix(real_t *s, int32_t row, int32_t col);
#endif




#endif // BASIC_MATRIX_OPERATIONS_H

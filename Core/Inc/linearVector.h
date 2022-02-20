#ifndef LINEARVECTOR_H
#define LINEARVECTOR_H

#include "matrix_types.h"

void setColons(matrix_t *pfVector, real_t fBegin, real_t fInterval, real_t fEnd);
#if CREAL_T
void setLinSpace(const creal_t begin, const creal_t endpoint, real_t count, matrix_t *X);
#else
void setLinSpace(const real_t begin, const real_t endpoint, real_t count, matrix_t *X);
#endif

#endif // LINEARVECTOR_H

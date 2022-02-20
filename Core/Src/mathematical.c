#include "mathematical.h"
#include <stdio.h>
#include <math.h>
#include <string.h>



void printMatrix(const matrix_t *pS)
{
    for(int i = 0; i < pS->size[0]; ++i) // row
    {
        for(int j = 0; j < pS->size[1]; ++j) // col
        {
#if SUPPORT_COMPLEX_NUMBER
//            printf("(%.2f)+(%.2fi) ", pS->data[i * pS->size[1] + j].re, pS->data[i * pS->size[1] + j].im);
#else
//            printf("%.3f ", pS->data[i * pS->size[1] + j].re);
#endif

        }

//        printf("\n");
    }
}

void fillMatrixDataRe(creal_t *data, const real_t *dataRe, int size)
{
    for(int i = 0; i < size; ++i)
    {
        data[i].re = dataRe[i];
    }
}

#if SUPPORT_COMPLEX_NUMBER
void fillMatrixDataIm(creal_t *data, const real_t *dataIm, int size)
{
    for(int i = 0; i < size; ++i)
    {
        data[i].im = dataIm[i];
    }
}
#endif

void transpose(const matrix_t *A, matrix_t *B)
{
  B->size[0] = A->size[1];
  B->size[1] = A->size[0];

  for (int i = 0; i < A->size[1]; i++) // size[0]
  {
    for (int j = 0; j < A->size[0]; j++) // size[1]
    {
      B->data[j + B->size[1] * i].re = A->data[i + A->size[1] * j].re;
#if SUPPORT_COMPLEX_NUMBER
      B->data[j + B->size[1] * i].im = -A->data[i + A->size[1] * j].im;
#endif
    }
  }
}

void setColons(matrix_t *pfVector, float fBegin, float fInterval, float fEnd)
{
  float fTemp0;
  float fTemp1;
  float fTemp3;
  float fDiff;
  float fNewEnd;
  int n;
  int fTemp2;

  if((fInterval == 0.0F) || ((fBegin < fEnd) && (fInterval < 0.0F)) ||
             ((fEnd < fBegin) && (fInterval > 0.0F)) || (fBegin == fEnd))
  {
        pfVector->size[0] = 0;
        pfVector->size[1] = 0;
  }
  else if (((float)floorf(fBegin) == fBegin) && ((float)floorf(fInterval) == fInterval))
  {
        fTemp2 = (int)(float)floorf((fEnd - fBegin) / fInterval);
        pfVector->size[1] = fTemp2 + 1;
        pfVector->size[0] = 1;

        for (int i = 0; i <= fTemp2; i++)
        {
            pfVector->data[i].re = fBegin + fInterval * (float)i;
        }

  }
  else
  {
    fTemp0 = floorf(((float)fEnd - fBegin) / fInterval + 0.5F);
    fTemp1 = fBegin + fTemp0 * fInterval;
    if (fInterval > 0.0F) {
      fDiff = fTemp1 - fEnd;
    } else {
      fDiff = fEnd - fTemp1;
    }

    if (fabsf(fDiff) < (FLT_EPSILON * fmaxf(fabsf(fBegin), fEnd)))
    {
      fTemp0++;
      fNewEnd = fEnd;
    }
    else if (fDiff > 0.0F)
    {
      fNewEnd = (fBegin + (fTemp0 - 1.0F) * fInterval);
    }
    else
    {
      fTemp0++;
      fNewEnd = fTemp1;
    }

    if (fTemp0 >= 0.0)
    {
      n = (int)fTemp0;
    }
    else
    {
      n = 0;
    }

    pfVector->size[0] = 1;
    pfVector->size[1] = n;

    if (n > 0)
    {
      pfVector->data[0].re = fBegin;
      if (n > 1)
      {
        pfVector->data[n - 1].re = fNewEnd;
        fTemp2 = (n - 1) / 2;
        for (int i = 0; i <= (fTemp2 - 2); i++)
        {
          fTemp3 = (float)(i + 1) * fInterval;
          pfVector->data[i + 1].re = fBegin + fTemp3;
          pfVector->data[(n - i) - 2].re = fNewEnd - fTemp3;
        }

        if (fTemp2 << 1 == n - 1)
        {
          pfVector->data[fTemp2].re = (fBegin + fNewEnd) / 2.0F;
        }
        else
        {
          fTemp3 = (float)fTemp2 * fInterval;
          pfVector->data[fTemp2].re = fBegin + fTemp3;
          pfVector->data[fTemp2 + 1].re = fNewEnd - fTemp3;
        }
      }
    }
  }
}

void setLinSpace(const creal_t begin, const creal_t endpoint, float count, matrix_t *X)
{
  int X_tmp;
  int i;
  int k;
  float delta2_re;
  float delta1_re;
  float delta2_im;
  float delta1_im;
  delta1_im = count;
  if (count < 0.0)
  {
    delta1_im = 0.0;
  }

  X->size[0] = 1;
  i = (int)floorf(delta1_im);
  X->size[1] = i;
  if (i >= 1)
  {
    X_tmp = i - 1;
    X->data[X_tmp] = endpoint;

    if (X->size[1] >= 2)
    {
      X->data[0] = begin;
      if (X->size[1] >= 3)
      {
        if ((begin.re == -endpoint.re) && (begin.im == -endpoint.im) && (i > 2))
        {
          for (k = 2; k <= X_tmp; k++)
          {
            delta1_im = (float)(((k << 1) - i) - 1) / ((float)i - 1.0);
            X->data[k - 1].re = delta1_im * endpoint.re;
            X->data[k - 1].im = delta1_im * endpoint.im;
          }

          if ((i & 1) == 1)
          {
            X_tmp = i >> 1;
            X->data[X_tmp].re = 0.0;
            X->data[X_tmp].im = 0.0;
          }
        }
        else if ((((begin.re < 0.0) != (endpoint.re < 0.0)) && ((fabs(begin.re)
          > FLT_MAX) || (fabsf(endpoint.re) >
                      FLT_MAX))) || (((begin.im < 0.0) !=
                     (endpoint.im < 0.0)) && ((fabsf(begin.im) >
                      FLT_MAX) || (fabsf(endpoint.im) >
                      FLT_MAX))))
        {
          if (begin.im == 0.0) {
            delta1_re = begin.re / ((float)X->size[1] - 1.0);
            delta1_im = 0.0;
          } else if (begin.re == 0.0) {
            delta1_re = 0.0;
            delta1_im = begin.im / ((float)X->size[1] - 1.0);
          } else {
            delta1_re = begin.re / ((float)X->size[1] - 1.0);
            delta1_im = begin.im / ((float)X->size[1] - 1.0);
          }

          if (endpoint.im == 0.0) {
            delta2_re = endpoint.re / ((float)X->size[1] - 1.0);
            delta2_im = 0.0;
          } else if (endpoint.re == 0.0) {
            delta2_re = 0.0;
            delta2_im = endpoint.im / ((float)X->size[1] - 1.0);
          } else {
            delta2_re = endpoint.re / ((float)X->size[1] - 1.0);
            delta2_im = endpoint.im / ((float)X->size[1] - 1.0);
          }

          X_tmp = X->size[1];
          for (k = 0; k <= X_tmp - 3; k++) {
            X->data[k + 1].re = (begin.re + delta2_re * ((float)k + 1.0)) -
              delta1_re * ((float)k + 1.0);
            X->data[k + 1].im = (begin.im + delta2_im * ((float)k + 1.0)) -
              delta1_im * ((float)k + 1.0);
          }
        } else {
          delta1_im = endpoint.re - begin.re;
          delta2_re = endpoint.im - begin.im;
          if (delta2_re == 0.0) {
            delta1_re = delta1_im / ((float)X->size[1] - 1.0);
            delta1_im = 0.0;
          } else if (delta1_im == 0.0) {
            delta1_re = 0.0;
            delta1_im = delta2_re / ((float)X->size[1] - 1.0);
          } else {
            delta1_re = delta1_im / ((float)X->size[1] - 1.0);
            delta1_im = delta2_re / ((float)X->size[1] - 1.0);
          }

          X_tmp = X->size[1];
          for (k = 0; k <= X_tmp - 3; k++) {
            X->data[k + 1].re = begin.re + ((float)k + 1.0) * delta1_re;
            X->data[k + 1].im = begin.im + ((float)k + 1.0) * delta1_im;
          }
        }
      }
    }
  }
}

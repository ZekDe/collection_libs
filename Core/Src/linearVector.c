#include "linearVector.h"
#include "math.h"

#if CREAL_T
void setColons(matrix_t *pfVector, real_t fBegin, real_t fInterval, real_t fEnd)
{
  real_t fTemp0;
  real_t fTemp1;
  real_t fTemp3;
  real_t fDiff;
  real_t fNewEnd;
  int32_t n;
  int32_t fTemp2;

  if((fInterval == 0.0F) || ((fBegin < fEnd) && (fInterval < 0.0F)) ||
             ((fEnd < fBegin) && (fInterval > 0.0F)) || (fBegin == fEnd))
  {
        pfVector->size[0] = 0;
        pfVector->size[1] = 0;
  }
  else if (((real_t)floorf(fBegin) == fBegin) && ((real_t)floorf(fInterval) == fInterval))
  {
        fTemp2 = (int32_t)(real_t)floorf((fEnd - fBegin) / fInterval);
        pfVector->size[1] = fTemp2 + 1;
        pfVector->size[0] = 1;

        for (int32_t i = 0; i <= fTemp2; i++)
        {
            pfVector->data[i].re = fBegin + fInterval * (real_t)i;
        }

  }
  else
  {
    fTemp0 = floorf(((real_t)fEnd - fBegin) / fInterval + 0.5F);
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
      n = (int32_t)fTemp0;
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
        for (int32_t i = 0; i <= (fTemp2 - 2); i++)
        {
          fTemp3 = (real_t)(i + 1) * fInterval;
          pfVector->data[i + 1].re = fBegin + fTemp3;
          pfVector->data[(n - i) - 2].re = fNewEnd - fTemp3;
        }

        if (fTemp2 << 1 == n - 1)
        {
          pfVector->data[fTemp2].re = (fBegin + fNewEnd) / 2.0F;
        }
        else
        {
          fTemp3 = (real_t)fTemp2 * fInterval;
          pfVector->data[fTemp2].re = fBegin + fTemp3;
          pfVector->data[fTemp2 + 1].re = fNewEnd - fTemp3;
        }
      }
    }
  }
}

void setLinSpace(const creal_t begin, const creal_t endpoint, real_t count, matrix_t *X)
{
  int32_t X_tmp;
  int32_t i;
  int32_t k;
  real_t delta2_re;
  real_t delta1_re;
  real_t delta2_im;
  real_t delta1_im;
  delta1_im = count;
  if (count < 0.0)
  {
    delta1_im = 0.0;
  }

  X->size[0] = 1;
  i = (int32_t)floorf(delta1_im);
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
            delta1_im = (real_t)(((k << 1) - i) - 1) / ((real_t)i - 1.0);
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
            delta1_re = begin.re / ((real_t)X->size[1] - 1.0);
            delta1_im = 0.0;
          } else if (begin.re == 0.0) {
            delta1_re = 0.0;
            delta1_im = begin.im / ((real_t)X->size[1] - 1.0);
          } else {
            delta1_re = begin.re / ((real_t)X->size[1] - 1.0);
            delta1_im = begin.im / ((real_t)X->size[1] - 1.0);
          }

          if (endpoint.im == 0.0) {
            delta2_re = endpoint.re / ((real_t)X->size[1] - 1.0);
            delta2_im = 0.0;
          } else if (endpoint.re == 0.0) {
            delta2_re = 0.0;
            delta2_im = endpoint.im / ((real_t)X->size[1] - 1.0);
          } else {
            delta2_re = endpoint.re / ((real_t)X->size[1] - 1.0);
            delta2_im = endpoint.im / ((real_t)X->size[1] - 1.0);
          }

          X_tmp = X->size[1];
          for (k = 0; k <= X_tmp - 3; k++) {
            X->data[k + 1].re = (begin.re + delta2_re * ((real_t)k + 1.0)) -
              delta1_re * ((real_t)k + 1.0);
            X->data[k + 1].im = (begin.im + delta2_im * ((real_t)k + 1.0)) -
              delta1_im * ((real_t)k + 1.0);
          }
        } else {
          delta1_im = endpoint.re - begin.re;
          delta2_re = endpoint.im - begin.im;
          if (delta2_re == 0.0) {
            delta1_re = delta1_im / ((real_t)X->size[1] - 1.0);
            delta1_im = 0.0;
          } else if (delta1_im == 0.0) {
            delta1_re = 0.0;
            delta1_im = delta2_re / ((real_t)X->size[1] - 1.0);
          } else {
            delta1_re = delta1_im / ((real_t)X->size[1] - 1.0);
            delta1_im = delta2_re / ((real_t)X->size[1] - 1.0);
          }

          X_tmp = X->size[1];
          for (k = 0; k <= X_tmp - 3; k++) {
            X->data[k + 1].re = begin.re + ((real_t)k + 1.0) * delta1_re;
            X->data[k + 1].im = begin.im + ((real_t)k + 1.0) * delta1_im;
          }
        }
      }
    }
  }
}

#else
void setColons(matrix_t *pfVector, real_t fBegin, real_t fInterval, real_t fEnd)
{
  real_t fTemp0;
  real_t fTemp1;
  real_t fTemp3;
  real_t fDiff;
  real_t fNewEnd;
  int32_t n;
  int32_t fTemp2;

  if((fInterval == 0.0F) || ((fBegin < fEnd) && (fInterval < 0.0F)) ||
             ((fEnd < fBegin) && (fInterval > 0.0F)) || (fBegin == fEnd))
  {
        pfVector->size[0] = 0;
        pfVector->size[1] = 0;
  }
  else if (((real_t)floorf(fBegin) == fBegin) && ((real_t)floorf(fInterval) == fInterval))
  {
        fTemp2 = (int32_t)(real_t)floorf((fEnd - fBegin) / fInterval);
        pfVector->size[1] = fTemp2 + 1;
        pfVector->size[0] = 1;

        for (int32_t i = 0; i <= fTemp2; i++)
        {
            pfVector->data[i] = fBegin + fInterval * (real_t)i;
        }

  }
  else
  {
    fTemp0 = floorf(((real_t)fEnd - fBegin) / fInterval + 0.5F);
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
      n = (int32_t)fTemp0;
    }
    else
    {
      n = 0;
    }

    pfVector->size[0] = 1;
    pfVector->size[1] = n;

    if (n > 0)
    {
      pfVector->data[0] = fBegin;
      if (n > 1)
      {
        pfVector->data[n - 1] = fNewEnd;
        fTemp2 = (n - 1) / 2;
        for (int32_t i = 0; i <= (fTemp2 - 2); i++)
        {
          fTemp3 = (real_t)(i + 1) * fInterval;
          pfVector->data[i + 1] = fBegin + fTemp3;
          pfVector->data[(n - i) - 2] = fNewEnd - fTemp3;
        }

        if (fTemp2 << 1 == n - 1)
        {
          pfVector->data[fTemp2] = (fBegin + fNewEnd) / 2.0F;
        }
        else
        {
          fTemp3 = (real_t)fTemp2 * fInterval;
          pfVector->data[fTemp2] = fBegin + fTemp3;
          pfVector->data[fTemp2 + 1] = fNewEnd - fTemp3;
        }
      }
    }
  }
}

void setLinSpace(const real_t begin, const real_t endpoint, real_t count, matrix_t *X)
{
  real_t delta1;
  int X_tmp;
  int i;
  int k;
  real_t delta2;
  delta1 = count;
  if (count < 0.0) {
    delta1 = 0.0;
  }

  X->size[0] = 1;
  i = (int)floor(delta1);
  X->size[1] = i;

  if (i >= 1) {
    X_tmp = i - 1;
    X->data[X_tmp] = endpoint;
    if (X->size[1] >= 2)
    {
      X->data[0] = begin;
      if (X->size[1] >= 3)
      {
        if ((begin == -endpoint   ) && (i > 2))
        {
          for (k = 2; k <= X_tmp; k++) {
            X->data[k - 1] = endpoint * ((real_t)(((k << 1) - i) - 1) / ((real_t)i - 1.0));
          }

          if ((i & 1) == 1)
          {
            X->data[i >> 1] = 0.0;
          }
        }
        else if (((begin < 0.0) != (endpoint < 0.0)) && ((fabs(begin) >
                     8.9884656743115785E+307) || (fabs(endpoint) >
                     8.9884656743115785E+307)))
        {
          delta1 = begin / ((real_t)X->size[1] - 1.0);
          delta2 = endpoint / ((real_t)X->size[1] - 1.0);
          X_tmp = X->size[1];
          for (k = 0; k <= X_tmp - 3; k++)
          {
            X->data[k + 1] = (begin + delta2 * ((real_t)k + 1.0)) - delta1 *
              ((real_t)k + 1.0);
          }
        }
        else
        {
          delta1 = (endpoint - begin) / ((real_t)X->size[1] - 1.0);
          X_tmp = X->size[1];
          for (k = 0; k <= X_tmp - 3; k++)
          {
            X->data[k + 1] = begin + ((real_t)k + 1.0) * delta1;
          }
        }
      }
    }
  }
}


#endif

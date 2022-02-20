#include "basic_matrix_operations.h"
#include <stdio.h>
#include <math.h>
#include <string.h>


void transpose(const matrix_t *A, matrix_t *B)
{
  B->size[0] = A->size[1];
  B->size[1] = A->size[0];

  for (int32_t i = 0; i < A->size[0]; i++)
  {
    for (int32_t j = 0; j < A->size[1]; j++)
    {
#if CREAL_T
      B->data[j + B->size[0] * i].re = A->data[i + A->size[0] * j].re;
      B->data[j + B->size[0] * i].im = -A->data[i + A->size[0] * j].im;
#else
      B->data[j + B->size[0] * i] = A->data[i + A->size[0] * j];
#endif
    }
  }
}

void printMatrix(const matrix_t *pS)
{
//    printf("(%.2f)+(%.2fi) ", pS->data[i * pS->size[1] + j].re, pS->data[i * pS->size[1] + j].im);
    for (int32_t i = 0; i < pS->size[0U]; i++)
    {
        for (int32_t j = 0; j < pS->size[1U]; j++)
        {
#if CREAL_T
//          printf("(%.2f)+(%.2fi) ", pS->data[i + pS->size[0] * j].re, pS->data[i + pS->size[0] * j].im);
#else
//          printf("(%.2f)", pS->data[i + pS->size[0] * j]);
#endif
        }
//        printf("\n");
      }
}

#if CREAL_T
void alignMatrix(creal_t *s, int32_t row, int32_t col)
{
   int32_t k = 0;
   int32_t rowCol = row * col;
   creal_t sTemp[rowCol];

   memcpy(sTemp, s, row * col * sizeof(creal_t));

  for (int32_t i = 0; i < row; i++)
  {
    for (int32_t j = 0; j < col; j++)
    {
      s[i + row * j].re = sTemp[k].re;
      s[i + row * j].im = sTemp[k].im;
      ++k;
    }
  }
}

void multiply(const matrix_t *A, const matrix_t *B, matrix_t *C)
{
  int32_t m;
  int32_t i;
  int32_t inner;
  int32_t n;
  int32_t j;
  int32_t coffset;
  int32_t boffset;
  int32_t b_i;
  int32_t k;
  int32_t aoffset;
  int32_t temp_re_tmp;
  real_t temp_re;
  real_t temp_im;

  if ((A->size[1] == 1) || (B->size[0] == 1))
  {
    C->size[0] = A->size[0];
    C->size[1] = B->size[1];

    m = A->size[0];

    for (i = 0; i < m; i++)
    {
      inner = B->size[1];

      for (n = 0; n < inner; n++)
      {
        C->data[i + (C->size[0] * n)].re = 0.0F;
        C->data[i + (C->size[0] * n)].im = 0.0F;
        j = A->size[1];
        for (coffset = 0; coffset < j; coffset++)
        {
          C->data[i + (C->size[0] * n)].re += (A->data[i + (A->size[0] * coffset)]
            .re * B->data[coffset + (B->size[0] * n)].re) - (A->data[i +
            (A->size[0] * coffset)].im * B->data[coffset + (B->size[0] * n)].im);

          C->data[i + (C->size[0] * n)].im += (A->data[i + (A->size[0] * coffset)]
            .re * B->data[coffset + (B->size[0] * n)].im) + (A->data[i +
            (A->size[0] * coffset)].im * B->data[coffset + (B->size[0] * n)].re);

        }
      }
    }
  }
  else
  {
    m = A->size[0];
    inner = A->size[1];
    n = B->size[1];
    C->size[0] = A->size[0];
    C->size[1] = B->size[1];

    for (j = 0; j < n; j++)
    {
      coffset = j * m;
      boffset = j * inner;
      for (b_i = 0; b_i < m; b_i++)
      {
        i = coffset + b_i;
        C->data[i].re = 0.0F;
        C->data[i].im = 0.0F;
      }

      for (k = 0; k < inner; k++)
      {
        aoffset = k * m;
        temp_re_tmp = boffset + k;
        temp_re = B->data[temp_re_tmp].re;
        temp_im = B->data[temp_re_tmp].im;

        for (b_i = 0; b_i < m; b_i++)
        {
          temp_re_tmp = aoffset + b_i;
          i = coffset + b_i;

          C->data[i].re += (temp_re * A->data[temp_re_tmp].re) - (temp_im *
            A->data[temp_re_tmp].im);

          C->data[i].im += (temp_re * A->data[temp_re_tmp].im) + (temp_im *
            A->data[temp_re_tmp].re);
        }
      }
    }
  }
}
#else
void alignMatrix(real_t *s, int32_t row, int32_t col)
{
   int32_t k = 0;
   int32_t rowCol = row * col;
   real_t sTemp[rowCol];

   memcpy(sTemp, s, row * col * sizeof(real_t));

  for (int32_t i = 0; i < row; i++)
  {
    for (int32_t j = 0; j < col; j++)
    {
      s[i + row * j] = sTemp[k];
      ++k;
    }
  }
}
void multiply(const matrix_t *A, const matrix_t *B, matrix_t *C)
{
  int32_t m;
  int32_t i;
  int32_t inner;
  int32_t n;
  int32_t j;
  int32_t coffset;
  int32_t boffset;
  int32_t b_i;
  int32_t k;
  int32_t aoffset;
  real_t temp;

  if ((A->size[1] == 1) || (B->size[0] == 1))
  {
    C->size[0] = A->size[0];
    C->size[1] = B->size[1];
    m = A->size[0];
    for (i = 0; i < m; i++)
    {
      inner = B->size[1];
      for (n = 0; n < inner; n++)
      {
        C->data[i + C->size[0] * n] = 0.0F;
        j = A->size[1];
        for (coffset = 0; coffset < j; coffset++)
        {
          C->data[i + C->size[0] * n] += A->data[i + A->size[0] * coffset] *
            B->data[coffset + B->size[0] * n];
        }
      }
    }
  } else {
    m = A->size[0];
    inner = A->size[1];
    n = B->size[1];
    C->size[0] = A->size[0];
    C->size[1] = B->size[1];
    for (j = 0; j < n; j++)
    {
      coffset = j * m;
      boffset = j * inner;
      for (b_i = 0; b_i < m; b_i++)
      {
        C->data[coffset + b_i] = 0.0F;
      }

      for (k = 0; k < inner; k++)
      {
        aoffset = k * m;
        temp = B->data[boffset + k];
        for (b_i = 0; b_i < m; b_i++)
        {
          i = coffset + b_i;
          C->data[i] += temp * A->data[aoffset + b_i];
        }
      }
    }
  }
}

#endif


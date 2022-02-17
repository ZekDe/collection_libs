/*
 * mathematical.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Duatepe
 */
#include "mathematical.h"

/**
 * \fn void printMatrix(const float*, uint32_t, uint32_t)
 * \brief : example
 * float C[6] = {1, 2,
              	 3, 4,
              	 6, 7};
    printMatrix(C, 3, 2);
 * \param pfIn : matrix
 * \param dwRow : matrix number of row
 * \param dwCol : matrix number of column
 */
void printMatrix(const float *pfIn, uint32_t dwRow, uint32_t dwCol)
{
	for(uint32_t i = 0; i < dwRow; ++i)
	{
		for(uint32_t j = 0; j < dwCol; ++j)
		{
			//printf("%f ", pfIn[i * dwCol + j]);
		}
		//printf("\n");
	}
}

uint32_t setVector(float fBegin, float fInterval, float fEnd, float *pfVector)
{
  uint32_t i;
  float fTemp0;
  float fTemp1;
  uint32_t fTemp2;
  float fDiff;
  float fBeginAbs;
  float fEndAbs;
  float fNewEnd;
  int n;
  float fTemp3;
  uint32_t retVal = 0;

  if((fInterval == 0.0F) || ((fBegin < fEnd) && (fInterval < 0.0F)) ||
             ((fEnd < fBegin) && (fInterval > 0.0F)) || (fBegin == fEnd))
  {
        retVal = 0;
  }
  else if (((float)floorf(fBegin) == fBegin) && ((float)floorf(fInterval) == fInterval))
  {
        fTemp2 = (int)(float)floorf((fEnd - fBegin) / fInterval);
        retVal = fTemp2 + 1;
        for (i = 0; i <= fTemp2; i++)
	    {
            pfVector[i] = fBegin + fInterval * (float)i;
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

    fBeginAbs = fabsf(fBegin);
    fEndAbs = fabsf(fEnd);
    if (fBeginAbs > fEndAbs)
    {
      fEndAbs = fBeginAbs;
    }

    if (fabsf(fDiff) < (k_FLT_EPSILON * fmaxf(fabsf(fBegin), fEnd)))
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
      n = (uint32_t)fTemp0;
    }
    else
    {
      n = 0;
    }

    retVal = n;

    if (n > 0)
    {
      pfVector[0] = fBegin;
      if (n > 1)
      {
        pfVector[n - 1] = fNewEnd;
        fTemp2 = (n - 1) / 2;
        for (i = 0; i <= (fTemp2 - 2); i++)
        {
          fTemp3 = (float)(i + 1) * fInterval;
          pfVector[i + 1] = fBegin + fTemp3;
          pfVector[(n - i) - 2] = fNewEnd - fTemp3;
        }

        if (fTemp2 << 1 == n - 1)
        {
          pfVector[fTemp2] = (fBegin + fNewEnd) / 2.0F;
        }
        else
        {
          fTemp3 = (float)fTemp2 * fInterval;
          pfVector[fTemp2] = fBegin + fTemp3;
          pfVector[fTemp2 + 1] = fNewEnd - fTemp3;
        }
      }
    }
  }
  return retVal;
}

/**
 * \fn void diag(const float[], float[], uint32_t)
 * \brief : example
 * float a[4] = {1,2,3,4};
 * float out[16];
 * diag(a,out,4);
 * \param pfIn : diagonal numbers of matrix size of rowCol
 * \param pfOut : diagonal matrix size of rowCol * rowCol
 * \param dwRowCol : number of row and column
 */
void diag(const float *pfIn, float *pfOut, uint32_t dwRowCol)
{
  memset(&pfOut[0], 0, dwRowCol * dwRowCol * sizeof(float));

  for (uint32_t j = 0; j < dwRowCol; j++)
  {
	 pfOut[j + (dwRowCol * j)] = pfIn[j];
  }
}


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
  float temp0;
  float temp1;
  float temp4;
  float cdiff;
  float fBeginAbs;
  float fEndAbs;
  float bnew;
  uint32_t temp3;
  uint32_t n;
  uint32_t retVal = 0;

  if((fInterval == 0.0F) || ((fBegin < fEnd) && (fInterval < 0.0F)) ||
             ((fEnd < fBegin) && (fInterval > 0.0F)) || (fBegin == fEnd))
  {
        retVal = 0;
  }
  else if (((float)floorf(fBegin) == fBegin) && ((float)floorf(fInterval) == fInterval))
  {
        temp3 = (uint32_t)(float)floorf((fEnd - fBegin) / fInterval);
        retVal = temp3 + 1;
        for (uint32_t i = 0; i <= temp3; i++)
	    {
            pfVector[i] = fBegin + fInterval * (float)i;
        }

  }
  else
  {
    temp0 = floor(((float)fEnd - fBegin) / fInterval + 0.5);
    temp1 = fBegin + temp0 * fInterval;
    if (fInterval > 0.0F) {
      cdiff = temp1 - fEnd;
    } else {
      cdiff = fEnd - temp1;
    }

    fBeginAbs = fabs(fBegin);
    fEndAbs = fabs(fEnd);
    if (fBeginAbs > fEndAbs)
    {
      fEndAbs = fBeginAbs;
    }

    if (fabs(cdiff) < EPSILON * fEndAbs)
    {
      temp0++;
      bnew = fEnd;
    }
    else if (cdiff > 0.0)
    {
      bnew = (float)(fBegin + (temp0 - 1.0) * fInterval);
    }
    else
    {
      temp0++;
      bnew = (float)temp1;
    }

    if (temp0 >= 0.0)
    {
      n = (int)temp0;
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
        pfVector[n - 1] = bnew;
        temp3 = (n - 1) / 2;
        for (uint32_t i = 0; i <= temp3 - 2; i++)
        {
          temp4 = (float)(i + 1) * fInterval;
          pfVector[i + 1] = fBegin + temp4;
          pfVector[(n - i) - 2] = bnew - temp4;
        }

        if (temp3 << 1 == n - 1)
        {
          pfVector[temp3] = (fBegin + bnew) / 2.0F;
        }
        else
        {
          temp4 = (float)temp3 * fInterval;
          pfVector[temp3] = fBegin + temp4;
          pfVector[temp3 + 1] = bnew - temp4;
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


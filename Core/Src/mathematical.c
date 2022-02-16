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

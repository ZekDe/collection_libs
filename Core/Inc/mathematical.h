/*
 * mathematical.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Duatepe
 */

#ifndef MATHEMATICAL_
#define MATHEMATICAL_H

#define k_FLT_EPSILON     0.0000001192093F
void printMatrix(const float *pfIn, uint32_t dwRow, uint32_t dwCol);
uint32_t setVector(float fBegin, float fInterval, float fEnd, float *pfVector);
void diag(const float *pfIn, float *pfOut, uint32_t dwRowCol);


#endif /* MATHEMATICAL_H */

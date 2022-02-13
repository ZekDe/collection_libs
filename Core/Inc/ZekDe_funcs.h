#ifndef ZEKDE_FUNCS_H
#define ZEKDE_FUNCS_H

#include "stdint.h"
#include "stdbool.h"

void vRisingEdgeDetection(_Bool catch, void(*cb)(void));
_Bool oRisingEdgeDetection(_Bool catch);
void vSeal(_Bool seal, _Bool breakTheSeal, _Bool *out);
void vSR_FF(_Bool S, _Bool R, _Bool *Q);

#endif /* ZEKDE_FUNCS_H */

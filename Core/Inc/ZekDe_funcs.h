#ifndef ZEKDE_FUNCS_H
#define ZEKDE_FUNCS_H

#include "stdint.h"
#include "stdbool.h"

void vRisingEdgeDetection(_Bool oCatch, void(*cb)(void));
_Bool oRisingEdgeDetection(_Bool oCatch);
void seal(_Bool oSeal, _Bool oBreakTheSeal, _Bool *poOut);
void SR(_Bool oS, _Bool oR, _Bool *poQ);

#endif /* ZEKDE_FUNCS_H */

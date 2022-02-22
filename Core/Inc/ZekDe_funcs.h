#ifndef ZEKDE_FUNCS_H
#define ZEKDE_FUNCS_H

#include "stdint.h"
#include "stdbool.h"

#define COLORS \
    X(RED)     \
    X(BLACK)   \
    X(WHITE)   \
    X(BLUE)
  
// Creating an enum of colors
// by macro expansion.
typedef enum colors {
    #define X(value) value,
        COLORS
    #undef X
}colors_t;

void vRisingEdgeDetection(_Bool oCatch, void(*cb)(void));
_Bool oRisingEdgeDetection(_Bool oCatch);
void seal(_Bool oSeal, _Bool oBreakTheSeal, _Bool *poOut);
void SR(_Bool oS, _Bool oR, _Bool *poQ);
float map(float fx, float fInMin, float fInMax,
			   float fOutMin, float fOutMax);

#endif /* ZEKDE_FUNCS_H */

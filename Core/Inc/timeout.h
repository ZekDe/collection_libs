#ifndef TIMEOUT_H
#define TIMEOUT_H

#include "stdint.h"
#include "stdbool.h"

// these macros are used to control "vTimeoutCheck
#define TIMEOUT_EN(t, x)				(t)->in = (x)
#define TIMEOUT_SET_INTERVAL(t, x)	(t)->interval = (x)



typedef struct
{
	_Bool in;
	_Bool aux;
	uint32_t interval;
	uint32_t since;
} timeout_t;

typedef struct
{
	_Bool aux;
	uint32_t since;
} ton_t;

void vTimeoutCheck(timeout_t *t, const uint32_t *now, void(*cb)(void));
_Bool oTON(ton_t *t, _Bool in, const uint32_t *now, uint32_t presetTime);


#endif /* TIMEOUT_H */

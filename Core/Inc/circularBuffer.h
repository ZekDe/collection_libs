#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include "stdint.h"

typedef struct
{
	uint32_t sz;
	void *buffer;
	void *buffer_end;
	void *head;
	void *tail;
}circularBuffer_t;

typedef enum
{
	CB_FAILED = 0,
	CB_SUCCESS ,
	CB_OVERFLOW,
	CB_EMPTY,
}circularBuffer_error_t;

circularBuffer_error_t eCBInit(circularBuffer_t *cb, void *buffer, uint32_t capacity, uint32_t sz);
uint32_t dwCBlength(circularBuffer_t *cb);
circularBuffer_error_t eCBWrite(circularBuffer_t *cb, const void *item);
circularBuffer_error_t eCBRead(circularBuffer_t *cb, void *item);


#endif /* CIRCULARBUFFER_H */

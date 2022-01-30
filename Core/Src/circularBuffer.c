#include "circularBuffer.h"
#include "string.h"

circularBuffer_error_t eCBInit(circularBuffer_t *cb, void *buffer, uint32_t capacity, uint32_t sz)
{
  const uint32_t incremented_capacity = capacity + 1; // Add extra element to evaluate count
  if((buffer == NULL) || (cb == NULL) || (sz == 0))
  {
	  return CB_FAILED;
  }
  cb->buffer = buffer;
  cb->buffer_end = (char *)cb->buffer + incremented_capacity * sz;
  cb->sz = sz;
  cb->head = cb->buffer;
  cb->tail = cb->buffer;

  return CB_SUCCESS;
}

uint32_t dwCBlength(circularBuffer_t *cb)
{
	return (uint32_t)(int32_t)((char *)cb->buffer_end - (char *)cb->buffer);
}

circularBuffer_error_t eCBWrite(circularBuffer_t *cb, const void *item)
{
  const uint32_t buffer_length = dwCBlength(cb);
  const uint32_t capacity_length = buffer_length - cb->sz;
  const uint32_t tail_head = (uint32_t)(int32_t)((char *)cb->tail - (char *)cb->head);
  const uint32_t head_tail = (uint32_t)(int32_t)((char *)cb->head - (char *)cb->tail);

  if ((tail_head == cb->sz) || (head_tail == capacity_length))
  {
	  return CB_OVERFLOW;
  }

  memcpy(cb->head, item, cb->sz);

  cb->head = (char*)cb->head + cb->sz;
  if(cb->head == cb->buffer_end)
  {
	  cb->head = cb->buffer;
  }

  return CB_SUCCESS;
}

circularBuffer_error_t eCBRead(circularBuffer_t *cb, void *item)
{
  if(cb->head == cb->tail)
  {
	  return CB_EMPTY;
  }

  memcpy(item, cb->tail, cb->sz);

  cb->tail = (char*)cb->tail + cb->sz;

  if(cb->tail == cb->buffer_end)
  {
	  cb->tail = cb->buffer;
  }

  return CB_SUCCESS;
}


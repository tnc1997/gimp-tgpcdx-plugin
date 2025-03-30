#include "circular_buffer.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
circular_buffer_free (const CircularBuffer *circular_buffer)
{
  free (circular_buffer->start);

  return 0;
}

int
circular_buffer_init (CircularBuffer *circular_buffer,
                      const size_t    capacity,
                      const size_t    size)
{
  if ((circular_buffer->start = malloc (capacity * size)) == NULL)
    {
      return -1;
    }

  circular_buffer->end      = circular_buffer->start + capacity * size;
  circular_buffer->head     = circular_buffer->start;
  circular_buffer->tail     = circular_buffer->start;
  circular_buffer->capacity = capacity;
  circular_buffer->size     = 0;

  return 0;
}

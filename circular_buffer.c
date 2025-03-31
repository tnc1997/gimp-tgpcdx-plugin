#include "circular_buffer.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int circular_buffer_get_element_size (const CircularBuffer *circular_buffer,
                                      size_t               *element_size);

int
circular_buffer_free (const CircularBuffer *circular_buffer)
{
  free (circular_buffer->start);

  return 0;
}

int
circular_buffer_get_capacity (const CircularBuffer *circular_buffer,
                              size_t               *capacity)
{
  *capacity = circular_buffer->capacity;

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

int
circular_buffer_is_empty (const CircularBuffer *circular_buffer, bool *is_empty)
{
  *is_empty = circular_buffer->size == 0;

  return 0;
}

int
circular_buffer_is_full (const CircularBuffer *circular_buffer, bool *is_full)
{
  *is_full = circular_buffer->size == circular_buffer->capacity;

  return 0;
}

int
circular_buffer_pop_element (CircularBuffer *circular_buffer, void *element)
{
  size_t element_size;

  circular_buffer_get_element_size (circular_buffer, &element_size);

  if (memcpy (element, circular_buffer->tail, element_size) == NULL)
    {
      return -1;
    }

  circular_buffer->tail = circular_buffer->tail + element_size;

  if (circular_buffer->tail == circular_buffer->end)
    {
      circular_buffer->tail = circular_buffer->start;
    }

  if (circular_buffer->size > 0)
    {
      circular_buffer->size -= 1;
    }

  return 0;
}

int
circular_buffer_push_element (CircularBuffer *circular_buffer,
                              const void     *element)
{
  size_t element_size;

  circular_buffer_get_element_size (circular_buffer, &element_size);

  if (memcpy (circular_buffer->head, element, element_size) == NULL)
    {
      return -1;
    }

  circular_buffer->head = circular_buffer->head + element_size;

  if (circular_buffer->head == circular_buffer->end)
    {
      circular_buffer->head = circular_buffer->start;
    }

  if (circular_buffer->size < circular_buffer->capacity)
    {
      circular_buffer->size += 1;
    }

  return 0;
}

int
circular_buffer_get_element_size (const CircularBuffer *circular_buffer,
                                  size_t               *element_size)
{
  *element_size = (circular_buffer->end - circular_buffer->start) /
                  circular_buffer->capacity;

  return 0;
}

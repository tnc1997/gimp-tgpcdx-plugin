#include "circular_buffer.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CircularBuffer
{
  void  *start;
  void  *end;
  void  *head;
  void  *tail;
  size_t capacity;
  size_t size;
};

size_t get_element_size (const CircularBuffer *circular_buffer);

void
circular_buffer_free (CircularBuffer *circular_buffer)
{
  free (circular_buffer->start);

  free (circular_buffer);
}

size_t
circular_buffer_get_capacity (const CircularBuffer *circular_buffer)
{
  return circular_buffer->capacity;
}

void *
circular_buffer_get_element_at (const CircularBuffer *circular_buffer,
                                const size_t          index)
{
  const size_t element_size = get_element_size (circular_buffer);

  void *element;

  if ((element = malloc (element_size)) == NULL)
    {
      return NULL;
    }

  if (memcpy (element, circular_buffer->start + index, element_size) == NULL)
    {
      return NULL;
    }

  return element;
}

size_t
circular_buffer_get_reserve (const CircularBuffer *circular_buffer)
{
  return circular_buffer->capacity - circular_buffer->size;
}

size_t
circular_buffer_get_size (const CircularBuffer *circular_buffer)
{
  return circular_buffer->size;
}

CircularBuffer *
circular_buffer_init (const size_t capacity, const size_t size)
{
  CircularBuffer *circular_buffer;

  if ((circular_buffer = malloc (sizeof (CircularBuffer))) == NULL)
    {
      return NULL;
    }

  if ((circular_buffer->start = malloc (capacity * size)) == NULL)
    {
      return NULL;
    }

  circular_buffer->end      = circular_buffer->start + capacity * size;
  circular_buffer->head     = circular_buffer->start;
  circular_buffer->tail     = circular_buffer->start;
  circular_buffer->capacity = capacity;
  circular_buffer->size     = 0;

  return circular_buffer;
}

bool
circular_buffer_is_empty (const CircularBuffer *circular_buffer)
{
  return circular_buffer->size == 0;
}

bool
circular_buffer_is_full (const CircularBuffer *circular_buffer)
{
  return circular_buffer->size == circular_buffer->capacity;
}

void *
circular_buffer_pop_element (CircularBuffer *circular_buffer)
{
  const size_t element_size = get_element_size (circular_buffer);

  void *element;

  if ((element = malloc (element_size)) == NULL)
    {
      return NULL;
    }

  if (memcpy (element, circular_buffer->tail, element_size) == NULL)
    {
      return NULL;
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

  return element;
}

void
circular_buffer_push_element (CircularBuffer *circular_buffer,
                              const void     *element)
{
  const size_t element_size = get_element_size (circular_buffer);

  if (memcpy (circular_buffer->head, element, element_size) == NULL)
    {
      return;
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
}

size_t
get_element_size (const CircularBuffer *circular_buffer)
{
  return (circular_buffer->end - circular_buffer->start) /
         circular_buffer->capacity;
}

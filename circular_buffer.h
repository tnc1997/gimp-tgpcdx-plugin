#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stddef.h>

typedef struct _CircularBuffer CircularBuffer;

struct _CircularBuffer
{
  void  *start;
  void  *end;
  void  *head;
  void  *tail;
  size_t capacity;
  size_t size;
};

int circular_buffer_free (const CircularBuffer *circular_buffer);

int circular_buffer_init (CircularBuffer *circular_buffer,
                          size_t          capacity,
                          size_t          size);

int circular_buffer_is_empty (const CircularBuffer *circular_buffer,
                              bool                 *is_empty);

int circular_buffer_is_full (const CircularBuffer *circular_buffer,
                             bool                 *is_full);

#endif

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

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

#endif

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stddef.h>

typedef struct CircularBuffer CircularBuffer;

void circular_buffer_free (CircularBuffer *circular_buffer);

size_t circular_buffer_get_capacity (const CircularBuffer *circular_buffer);

void *circular_buffer_get_element_at (const CircularBuffer *circular_buffer,
                                      size_t                index);

size_t circular_buffer_get_reserve (const CircularBuffer *circular_buffer);

size_t circular_buffer_get_size (const CircularBuffer *circular_buffer);

CircularBuffer *circular_buffer_init (size_t capacity, size_t size);

bool circular_buffer_is_empty (const CircularBuffer *circular_buffer);

bool circular_buffer_is_full (const CircularBuffer *circular_buffer);

void *circular_buffer_pop_element (CircularBuffer *circular_buffer);

void circular_buffer_push_element (CircularBuffer *circular_buffer,
                                   const void     *element);

#endif

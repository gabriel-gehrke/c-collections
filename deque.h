#ifndef C_COLLECTIONS_DEQUE_H
#define C_COLLECTIONS_DEQUE_H

#include "collection.h"

typedef struct {
    // the number of elements currently inserted into the deque
    size_t size;
    // the allocated capacity of the deque's array
    size_t capacity;

    // the head of the deque. if size > 0 it points to the first element in the deque.
    size_t head;
    // the tail of the deque. if size > 0 it points to the spot after the last element in the deque.
    size_t tail;

    // used to mark if the deque is resizeable.
    bool resizeable;

    // the array backing the deque
    void** array;
} deque;

deque deque_new(size_t capacity);

deque deque_wrap(void** array, size_t capacity);

bool deque_append(deque* d, void* element);

bool deque_prepend(deque* d, void* element);

void* deque_shift(deque* d);

void* deque_pop(deque* d);

bool deque_ensure_capacity(deque* d, size_t capacity);

#endif // C_COLLECTIONS_DEQUE_H
#include "deque.h"
#include "stack.h"

static inline size_t min(size_t a, size_t b) {
    return (a <= b) ? a : b;
}

static bool deque_grow(deque* d, size_t capacity) {
    // copy elements to temporary array
    const size_t s = d->size;
    void* temp[s];
    for (size_t i = 0; i < s; i++) {
        temp[i] = deque_shift(d);
    }

    // realloc backed array
    void** new_arr = realloc(d->array, capacity * sizeof(void**));
    if (new_arr == NULL) return false;
    d->array = new_arr;
    d->capacity = capacity;

    // copy back
    d->head = 0;
    d->tail = 0;
    for (size_t i = 0; i < s; i++) {
        deque_append(d, temp[i]);
    }
}

deque deque_wrap(void** array, size_t capacity) {
    deque d = {
        .array = array,
        .capacity = capacity,
        .resizeable = false,
        .size = 0,
        .head = 0,
        .tail = 0
    };
    return d;
}

deque deque_new(size_t capacity) {
    void** array = (void**) malloc(capacity * sizeof(void**));
    deque d = deque_wrap(array, capacity);
    if (array == NULL) {
        d.capacity = 0;
    } else {
        d.resizeable = true;
    }
    return d;
}

bool deque_append(deque* d, void* element) { 
    if (d->size >= d->capacity) {
        // try to resize deque
        if (!deque_ensure_capacity(d, d->capacity << 1)) return false;
    }

    d->array[d->tail++] = element;

    if (d->tail >= d->capacity) {
        d->tail = 0;
    }

    d->size++;
    return true;
}

bool deque_prepend(deque* d, void* element) { 
    if (d->size >= d->capacity) {
        // try to resize deque
        if (!deque_ensure_capacity(d, d->capacity << 1)) return false;
    }

    if (d->head == 0) {
        d->head = d->capacity - 1;
    } else {
        d->head--;
    }
    d->array[d->head] = element;

    d->size++;
    return true;
}

void* deque_shift(deque* d) { 
    if (d->size == 0) return NULL;

    void* element = d->array[d->head++];
    if (d->head >= d->capacity) {
        d->head = 0;
    }

    d->size--;
    return element;
}

void* deque_pop(deque* d) { 
    if (d->size == 0) return NULL;

    if (d->tail == 0) {
        d->tail = d->capacity - 1;
    } else {
        d->tail--;
    }
    d->size--;

    return d->array[d->tail];
}

bool deque_ensure_capacity(deque* d, size_t capacity) { 
    if (d->capacity >= capacity) return true;
    if (!d->resizeable) return false;

    return deque_grow(d, capacity);
}

// UNTESTED
bool deque_insert_at(deque* d, void* element, const size_t pos) {
    if (d->size >= d->capacity) return false;
    if (pos > d->size) return false;

    if (pos == 0)           return deque_prepend(d, element);
    if (pos == d->size - 1) return deque_append(d, element);

    const size_t _s = min(pos, d->size - pos);
    void* temp[_s];
    stack temp_stack = stack_wrap(temp, _s);

    if (pos <= d->size / 2) {
        // insert item into front
        for (size_t i = 0; i < _s; i++) {
            stack_push(&temp_stack, deque_shift(d));
        }
        deque_prepend(d, element);
        for (size_t i = 0; i < _s; i++) {
            deque_prepend(d, stack_pop(&temp_stack));
        }
    } else {
        // insert item into back
        for (size_t i = 0; i < _s; i++) {
            stack_push(&temp_stack, deque_pop(d));
        }
        deque_append(d, element);
        for (size_t i = 0; i < _s; i++) {
            deque_append(d, stack_pop(&temp_stack));
        }
    }

    return true;
}

// UNTESTED
void* deque_get_at(deque* d, size_t pos) {
    if (pos >= d->size) return NULL;

    pos += d->head;
    if (pos >= d->size) pos -= d->size;

    return d->array[pos];
}
#include "stack.h"

static bool stack_grow(stack* s, size_t cap) {
    void** new_arr = (void**) realloc(s->array, cap * sizeof(void**));
    if (new_arr == NULL) {
        return false;
    }
    s->array = new_arr;
    s->capacity = cap;
    return true;
}

stack stack_wrap(void** array, size_t array_len) {
    stack s = {
        .size = 0,
        .capacity = array_len,
        .resizeable = false,
        .array = array
    };
    return s;
}

stack stack_new(size_t capacity) {
    void** array = (void**) malloc(capacity * sizeof(void**));
    stack s = stack_wrap(array, capacity);
    if (array == NULL) {
        s.capacity = 0;
    } else {
        s.resizeable = true;
    }
    return s;
}

bool stack_push(stack* s, void* elem) {
    if (s->size >= s->capacity) {
        // try to resize
        if (!stack_ensure_capacity(s, s->capacity << 1)) return false;
    }

    s->array[s->size++] = elem;
    return true;
}

void* stack_pop(stack* s) {
    if (s->size == 0) return NULL;

    return s->array[--s->size];
}

void* stack_peek(stack* s) {
    if (s->size == 0) return NULL;

    return s->array[s->size - 1];
}

bool stack_ensure_capacity(stack* s, size_t cap) {
    if (s->capacity >= cap) return true;
    if (!s->resizeable) return false;

    return stack_grow(s, cap);
}
#include "stack.h"

static void stack_grow(stack* s, size_t cap) {
    s->array = (void**) realloc(s->array, cap * sizeof(void**));
    s->capacity = cap;
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
    s.resizeable = true;
    return s;
}

bool stack_push(stack* s, void* elem) {
    if (s->size >= s->capacity) {
        // stack is full
        if (!s->resizeable) return false;

        stack_grow(s, s->capacity * 2);
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

    stack_grow(s, cap);
    return true;
}
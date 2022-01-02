#include "stack.h"

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

        s->capacity *= 2;
        s->array = (void**) realloc(s->array, s->capacity * sizeof(void**));
    }

    s->array[s->size++] = elem;
    return true;
}

void* stack_pop(stack* s) {
    if (s->size == 0) return NULL;

    return s->array[s->size--];
}

void* stack_head(stack* s) {
    return s->array[s->size];
}
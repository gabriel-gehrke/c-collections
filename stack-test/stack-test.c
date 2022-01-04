#include "../stack.h"
#include <stdio.h>

#define STACK_CAP 128
#define assert(statement) if (!(statement)) {fprintf(stderr, "ERROR: Assertion failed: %s (%s:%d)\n", #statement, __FILE__, __LINE__); exit(1);} //else {printf("Assertion %s succeeded.\n", #statement);}

static void test_push(stack* s) {

    size_t start_size = s->size;
    size_t start_cap = s->capacity;

    // fill stack
    for (int i = start_size; i < s->capacity; i++) {
        void* val = (void*) ((unsigned int) rand()) + 1L;

        // test push
        assert(stack_push(s, val) == true);
        assert(s->size == start_size + i + 1);
        assert(s->capacity == start_cap);

        // test peek
        assert(stack_peek(s) == val);
        assert(s->size == start_size + i + 1);
    }

    if (s->resizeable) {
        assert(stack_push(s, (void*)42) == true);
        assert(s->capacity > start_cap);
    } else {
        assert(stack_push(s, (void*)42) == false);
    }
}

static void test_pop(stack* s) {
    size_t cap = s->capacity;
    size_t start_size = s->size;
    for (int i = 0; i < start_size; i++) {
        // test pop
        void* val = s->array[start_size - i - 1];
        assert(stack_pop(s) == val);
        assert(s->size == start_size - i - 1);
    }
    assert(s->size == 0);
    assert(stack_pop(s) == NULL);
}

static void test_stack_stack() {
    puts("Testing non-resizable stack allocation on main stack...");

    void* arr[128];
    stack _stack = stack_wrap(arr, sizeof(arr) / sizeof(void*));
    assert(_stack.resizeable == false);
    assert(_stack.capacity == STACK_CAP);
    assert(_stack.array != NULL);
    assert(_stack.size == 0);

    test_push(&_stack);
    test_pop(&_stack);
}

static void test_heap_stack() {
    puts("Testing resizable stack allocation on heap...");

    stack _stack = stack_new(STACK_CAP);
    assert(_stack.resizeable == true);
    assert(_stack.capacity == STACK_CAP);
    assert(_stack.array != NULL);
    assert(_stack.size == 0);

    stack_ensure_capacity(&_stack, 2 * STACK_CAP);
    assert(_stack.capacity == 2 * STACK_CAP);

    test_push(&_stack);
    test_pop(&_stack);

}

int main() {

    test_stack_stack();
    test_heap_stack();
    
    puts("\nAll Assertions succeeded.");

    return 0;
}
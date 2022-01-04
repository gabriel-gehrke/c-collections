#ifndef C_COLLECTIONS_STACK_H
#define C_COLLECTIONS_STACK_H

#include "collection.h"

/**
 * @brief An array-based stack data structure.
 * 
 * It can be allocated by calling stack_new() or by creating an array and calling
 * stack_wrap().
 * 
 * By modifying the "resizeable" variable, 
 * it can be configured to have a fixed capacity or to be dynamically resizable (only works
 * when the stack's array was allocated on the heap).
 */
typedef struct {
    size_t size;
    size_t capacity;
    bool resizeable;
    void** array;
} stack;

/**
 * @brief Wraps an existing array (on stack or heap) with a stack data structure.
 * It is not going to attempt to resize itself by default.
 * @param array the array to wrap.
 * @param array_len the length of the array (in elements).
 * @return stack
 */
stack stack_wrap(void** array, size_t array_len);

/**
 * @brief Allocates a new stack with the given capacity on the heap.
 * If the elements exceed the capacity, it gets automatically increased.
 * 
 * @param capacity the capacity (in elements) of the new stack.
 * @return stack 
 */
stack stack_new(size_t capacity);

/**
 * @brief Pushes a pointer (element) to the stack.
 * @param s the stack.
 * @param elem the element.
 * @return true on success, otherwise false.
 */
bool stack_push(stack* s, void* elem);

/**
 * @brief Removes and returns the first item from the stack.
 * @param s the stack.
 * @return the removed element on success, otherwise NULL (Note: elements can be NULL).
 */
void* stack_pop(stack* s);

/**
 * @brief Returns top of stack without removing it.
 * @param s the stack.
 * @return the top item.
 */
void* stack_peek(stack* s);

/**
 * @brief Ensures, that the stack has capacity for at least "cap" elements. This method only
 * works for resizeable stacks.
 * 
 * @param s the stack.
 * @param cap the capacity.
 * @return true on success, false if capacity ensurance failed (perhaps because the stack is not resizeable)
 */
bool stack_ensure_capacity(stack* s, size_t cap);

#endif //C_COLLECTIONS_STACK_H
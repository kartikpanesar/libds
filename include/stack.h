#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Stack stack;

stack *stack_init(size_t element_size);

void *stack_push(stack *s, const void *value);
void stack_pop(stack *s);

const void *stack_peek(stack *s);

void stack_free(stack *s);


#endif

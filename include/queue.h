#ifndef QUEUE_H
#define QUEUE_H 

#include <stddef.h>
#include <stdbool.h>

typedef struct queue qu;

qu *queue_init(size_t element_size);

void enqueue(qu *q, void *value);
void dequeue(qu *q, void *out);

void queue_free(qu *q);

size_t queue_size(qu *q);
size_t queue_element_size(qu *q);

bool is_empty(qu *q);

#endif 

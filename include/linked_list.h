#ifndef QUEUE_H
#define QUEUE_H 

#include <stddef.h>

typedef struct double_linked_list dll;

dll *dll_init(size_t element_size);
void dll_free(dll *dull);

void dll_append(dll *dull, const void *value);
void dll_insert(dll *dull, int index, const void *value);

const void *dll_get(dll *dull, int index);
void dll_set(dll *dull, int index , const void *value);

#endif 

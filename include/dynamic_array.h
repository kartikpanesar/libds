#ifndef LINKED_LIST_H
#define LINKED_LIST_H 

#include <stddef.h>

typedef struct dynamic_array da ;

da *da_init(size_t element_size);

void da_append(da *pda, const void* value);

const void *da_get(da *pda , int index);
void da_set(da *pda , int index, const void *value);

void da_free(da *pda);


#endif

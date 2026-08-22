#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INITIAL_CAPACITY 50

// general type dynamic array 

typedef struct dynamic_array{
    void *items;
    size_t element_size;
    size_t count;
    size_t capacity;
} da;

da *da_init(size_t element_size){
    da *dynamic_array = malloc(sizeof(da));

    if(dynamic_array == NULL){
        fprintf(stderr, "could'nt create a dynamic array.\n");
        return NULL;
    }

    // intializing the memebers of the struct da(dynamic array).
    dynamic_array->items = NULL;
    dynamic_array->element_size = element_size;
    dynamic_array-> count = 0;
    dynamic_array->capacity = INITIAL_CAPACITY;

    void *tmp = malloc(INITIAL_CAPACITY * dynamic_array->element_size);
    if(tmp == NULL){
        fprintf(stderr, "couldn't allocate memory for intializing dynamic array.\n");
        return NULL;
    }
    dynamic_array->items = tmp;

    return dynamic_array;
}


void da_append(da *pda, const void *value){
    if(pda->count >= pda->capacity){
        pda->capacity *= 2;
        void *tmp = realloc(pda->items, pda->capacity * pda->element_size);

        if(tmp == NULL){
            fprintf(stderr,"Unable to allocate memory for adding an element .\n");
            exit(1);
        }
    }
    void *current_index = (char *)pda->items  + (pda->count * pda->element_size);
    memcpy(current_index, value, pda->element_size);
    
    pda->count++;
}


const void *da_get(da *dynamic_array, int index){
    const void *p = NULL;

    p = dynamic_array->items + (index * dynamic_array->element_size);
    return p;
}

void da_set(da *dynamic_array, int index, const void *value){
    void *current_index = dynamic_array->items + (index * dynamic_array->element_size);
    memcpy(current_index, value, dynamic_array->element_size);

    return;
}


void da_free(da *dynamic_array){
    free(dynamic_array->items);
    return ;
}








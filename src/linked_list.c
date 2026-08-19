# include <stdio.h>
# include <stdlib.h>
#include <string.h>


// Doubly Linked List .

typedef struct Node {
    struct Node *prev;
    void *value;
    struct Node *next;
} node;


typedef struct doubly_linked_list {
    size_t count;
    size_t element_size;
    node *head;
    node *tail;
} dll;


dll *dll_init(size_t element_size){
    dll *new = malloc(sizeof(dll));
    if(new==NULL){
        fprintf(stderr, "Couldn't allocate memory for creating a doubly linked list.\n");
        exit(1);
    }

    new->head = NULL;
    new->tail = NULL;
    new->count = 0;
    new->element_size = element_size;

    return new;
}

void dll_free(dll *dull){

    node *current = dull->head;
    node *next = NULL;

    while(current!= NULL){
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

    free(dull);
}


void dll_append(dll *dull, const void *v){
    void *value = malloc(dull->element_size);

    if(value==0){
        fprintf(stderr, "Couldn't allocate memory for appending the value.\n");
        exit(1);
    }

    // copy the bytes 
    memcpy(value, v, dull->element_size);

    node *new = malloc(sizeof(node));
    if(new==0){
        fprintf(stderr, "Couldn't allocate memory for new node.\n");
        exit(1);
    }

    new->value = value;
    new->next = NULL;

    if(dull->head == NULL){
        // if it's the first element.
        dull->head = new;
    }
    else{
        // if it's not the first element 
        dull->tail->next = new;
    }

    new->prev = dull->tail;
    dull->tail = new;
    dull->count++;


    return ;
}


const void *dll_get(dll *dull, size_t index){
    if(index >= dull->count){
        fprintf(stderr, "Index out of range.\n");
        exit(1);
    }

    node *current = dull->head;

    for(size_t i=0; i<index; i++){
        current = current->next;
    }

    return (const void *) current->value;
}


void dll_set(dll *dull, size_t index, const void *value){
    if(index >= dull->count){
        fprintf(stderr, "Index out of range.\n");
        exit(1);
    }

    node *current = dull->head;
    for(size_t i=0; i<index; i++){
        current = current->next;
    }


    void *v = malloc(dull->element_size);
    if(v==NULL){
        fprintf(stderr, "Couldn't allocate memory for new value.\n");
        exit(1);
    }

    // copying the value in the newly allocate memory.
    memcpy(v, value, dull->element_size);


    // freeing previous value;
    free(current->value);

    // assigning new value.
    current->value = v;

    return ;
}


void dll_insert(dll *dull, size_t index, const void *value){
    if(index >= dull->count){
        fprintf(stderr, "Index out of range.\n");
        exit(1);
    }


    void *v = malloc(dull->element_size);
    if(v==0){
        fprintf(stderr, "Couldn't allocate memory for the new value.\n");
        exit(1);
    }

    // copying the bytes 
    memcpy(v, value, dull->element_size);

    node *new = malloc(sizeof(node));
    if(new==0){
        fprintf(stderr, "Couldn't allocate memory for new node.\n");
        exit(1);
    }

    node *current = dull->head;
    for(size_t i=0; i<index-1; i++){
        current =current->next;
    }

    new->value = v;

    if(index==0){
        new->prev = NULL;
        new->next = dull->head;
        dull->head->prev = new;
        dull->head = new;
    }

    else{

        new->prev = current;
        new->next = current->next;

        current->next = new;

        new->next->prev = new;
    }

    dull->count ++;

    return ;
}



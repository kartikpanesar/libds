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
    node *head;
    node *tail;
    size_t count;
} dll;


dll *dll_init(){
    dll *new = malloc(sizeof(dll));
    if(new==NULL){
        fprintf(stderr, "Couldn't allocate memory for creating a doubly linked list.\n");
        exit(1);
    }

    new->head = NULL;
    new->tail = NULL;
    new->count = 0;

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


void dll_append(dll *dull, const void *v, size_t element_size){
    void *value = malloc(element_size);

    if(value==0){
        fprintf(stderr, "Couldn't allocate memory for appending the value.\n");
        exit(1);
    }

    // copy the bytes 
    memcpy(value, v, element_size);

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


void *dll_get(dll *dull, int index){
    if(index < 0 || index >= dull->count){
        fprintf(stderr, "Index out of range.\n");
        exit(1);
    }

    node *current = dull->head;

    for(int i=0; i<index; i++){
        current = current->next;
    }

    return current->value;
}


void dll_set(dll *dull, int index, const void *value , size_t element_size){
    if(index < 0 || index >= dull->count){
        fprintf(stderr, "Index out of range.\n");
        exit(1);
    }

    node *current = dull->head;
    for(int i=0; i<index; i++){
        current = current->next;
    }


    void *v = malloc(element_size);
    if(v==NULL){
        fprintf(stderr, "Couldn't allocate memory for new value.\n");
        exit(1);
    }

    // copying the value in the newly allocate memory.
    memcpy(v, value, element_size);


    // freeing previous value;
    free(current->value);

    // assigning new value.
    current->value = v;

    return ;
}


void dll_insert(dll *dull, int index, const void *value , size_t element_size){
    if(index < 0 || index >= dull->count){
        fprintf(stderr, "Index out of range.\n");
        exit(1);
    }


    void *v = malloc(element_size);
    if(v==0){
        fprintf(stderr, "Couldn't allocate memory for the new value.\n");
        exit(1);
    }

    // copying the bytes 
    memcpy(v, value, element_size);

    node *new = malloc(sizeof(node));
    if(new==0){
        fprintf(stderr, "Couldn't allocate memory for new node.\n");
        exit(1);
    }

    node *current = dull->head;
    for(int i=0; i<index-1; i++){
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



int main(){

    dll *dull = dll_init();

    dll_append(dull, "kartik", 7);
    dll_append(dull, "ritik", 6);
    dll_append(dull, "ankur", 6);

    printf("%s \n", (char *)dll_get(dull, 0));
    printf("%s \n", (char *)dll_get(dull, 1));
    printf("%s \n", (char *)dll_get(dull, 2));

    dll_insert(dull, 1, "naman", 6);

    printf("%s \n", (char *)dll_get(dull, 0));
    printf("%s \n", (char *)dll_get(dull, 1));
    printf("%s \n", (char *)dll_get(dull, 2));
    printf("%s \n", (char *)dll_get(dull, 3));

    dll_insert(dull, 3, "mandeep", 8);

    printf("%s \n", (char *)dll_get(dull, 0));
    printf("%s \n", (char *)dll_get(dull, 1));
    printf("%s \n", (char *)dll_get(dull, 2));
    printf("%s \n", (char *)dll_get(dull, 3));
    printf("%s \n", (char *)dll_get(dull, 4));



    dll_free(dull);
    return 0;
}


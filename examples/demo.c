#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Node{
    void *value;
    struct Node *next;

} node;


typedef struct {
    size_t count;
    size_t element_size;
    node *head;
    node *tail;
} qu;


qu *queue_init(size_t element_size){
    qu *q = malloc(sizeof(qu));
    if(q==0){
        fprintf(stderr, "couldn't allocate memory to initialize queue.\n");
        exit(1);
    }

    q->count = 0;
    q->head = 0;
    q->tail = 0;
    q->element_size = element_size;

    return q;
}


void enqueue(qu *q, const void *value){
    void *v = malloc(q->element_size);
    if(v==0){
        fprintf(stderr, "Couldn't allocate memory for value.\n");
        exit(1);
    }

    // copying bytes.
    memcpy(v, value, q->element_size);

    node *new = malloc(sizeof(node));

    if(new==0){
        fprintf(stderr, "Couldn't allocate memory to initialize new node.\n");
        exit(1);
    }

    new->value = v ;
    new->next = 0;

    if(q->count==0){
        q->head = new;
        q->tail = new;
    }
    else{
        q->tail->next = new;
        q->tail = new;
    }


    q->count++;

    return ;
}


void *dequeue(qu *q){
    if(q->count <= 0){
        fprintf(stderr, "Queue is empty\n");
        exit(1);
    }

    node *current = q->head;
    void *value = current->value;
    q->head = q->head->next;
    q->count--;

    // this frees the node , not the value at the node.
    // that needs to freed by the caller.
    free(current);

    return value;
}


void queue_free(qu *q){
    node *current = q->head;
    while(current!=NULL){
        node *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

    free(q);
}


size_t queue_size(qu *q){
    return q->count;
}


size_t queue_element_size(qu *q){
    if(q->count < 0){
        fprintf(stderr, "Queue is empty.\n");
        exit(1);
    }

    return q->element_size;
}


bool is_empty(qu *q){
    if(q->count>0){
        return false;
    }
    return true;
}


int main(){


    return 0;
} 



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT_CAPACITY 50

typedef struct Node{
    int value;
    struct Node *next;

} node;


typedef struct {
    size_t count;
    size_t capacity;
    node *head;

} qu;


qu *queue_init(){
    qu *q = malloc(sizeof(qu));
    if(q==0){
        fprintf(stderr, "couldn't allocate memory to initialize queue.\n");
        exit(1);
    }

    q->count = 0;
    q->capacity = INIT_CAPACITY;
    q->head = 0;

    return q;
}


void enqueue(qu *q, int value){
    node *new = malloc(sizeof(node));
    if(new==0){
        fprintf(stderr, "couldn't allocate memory for new element.\n");
        exit(1);
    }

    new->value = value;
    new->next = q->head;
    q->head = new;

    return;
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


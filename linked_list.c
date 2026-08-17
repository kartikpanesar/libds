# include <stdio.h>
# include <stdlib.h>

# define type(x) x

// Doubly Linked List .

typedef struct node {
    struct node *prev;
    int value;
    struct node *next;
} Node;

typedef struct linked_list {
    Node *head;
    Node *tail;
    int count;
} ll;

void ll_empty(ll *list){

    Node *current = list->head;
    Node *next = NULL;

    while(current!= NULL){
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
}

void ll_append(ll *list, int x){

    Node *new = malloc(sizeof(Node));
    if(new == NULL){
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }
    new->value = x;
    new->next = NULL; // if i am adding a new element , this would always be NULL.

    if(list->head == NULL){
        // means there are no nodes in our linked list .
        new->prev = NULL;
        list->head = new;

        list->tail = new;
    }

    else{
        // there is atleast 1 or more elements in our linked list.
        new->prev = list->tail;
        list->tail->next = new;
        list->tail = new;
    }

    // incrementing the count of the total nodes.
    list->count++;

    return ;
}


int main(){

    ll list = {.head = NULL, .tail = NULL, .count = 0};

    for(int i=1; i<=10; i++){
        ll_append(&list, i);
    }

    Node *current = list.head;
    for(int i=0; i<list.count; i++){
        printf("%d \n", current->value);
        current = current->next;
    }

    ll_empty(&list);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 50

typedef struct {
    void *start;
    void *top;
    size_t element_size;
    size_t count;
    size_t capacity;

} stack;

stack *stack_init(size_t element_size){
    stack *s = malloc(sizeof(stack));
    if(s==NULL){
        fprintf(stderr, "couldn't allocate memory to initialize stack object.\n");
        exit(1);
    }

    // Initialize the members of the stack;
    s->top = 0;
    s->count = 0;
    s->capacity = INIT_SIZE;
    s->element_size = element_size;
    s->start = malloc(s->capacity * s->element_size);

    if(s->start == 0){
        fprintf(stderr, "couldn't allocate memory to stack.\n");
        exit(1);
    }

    return s;
}


void stack_push(stack *s, const void *value){
    if(s->count >= s->capacity){
        s->capacity *= 2;

        void *tmp = realloc(s->start, s->capacity * s->element_size);
        if(tmp == NULL){
            fprintf(stderr, "Unable to allocate memory for the new_element.\n");
            exit(1);
        }

        s->start = tmp;
    }


    void *current = s->start + (s->count * s->element_size);

    memcpy(current, value, s->element_size);

    // update count and top
    s->count++;
    s->top = current;

    return;
}


void *stack_pop(stack *s){
    void *p = s->top;

    if(p==0){
        return 0;
    }

    if(s->top - s->element_size < s->start){
        s->top = 0;
        s->count--;
        return p;
    }

    // update top and count
    s->top = s->top - s->element_size;
    s->count--;

    return p;
}

void stack_free(stack *s){
    free(s->start);
    free(s);
}


int main(){

    char *names[5] = {"kartik", "ritik", "naman", "ankur", "mandeep"};
    stack *s = stack_init(sizeof(char *));

    for(int i=0; i<5; i++){
        stack_push(s, names[i]);
    }

    while(s->top!=NULL){
        printf("%s \n", (char *)stack_pop(s));
    }

    stack_free(s);

    return 0;
}

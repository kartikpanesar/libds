#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static size_t default_array_size = 32;


typedef struct Node{
    const char* key;
    void *obj ;
    struct Node *next;
} node;


typedef struct Map{
    size_t count;
    size_t capacity;
    node **array;
} map;


unsigned long hash_function_djb(map *m, const char *string){
    unsigned long hash = 5381;
    int c;

    while((c = *string++)){
        hash = ((hash << 5) + hash) + c;
    }

    return hash % m->capacity;
}


map* map_init(){
    map *m = malloc(sizeof(map));
    if(m==0){
        fprintf(stderr, "Couldn't allocate memory for initializing the map.\n");
        exit(1);
    }

    m->count = 0;
    m->capacity = default_array_size;

    void *tmp = calloc(default_array_size , sizeof(node*));

    if(tmp==0){
        fprintf(stderr, "Couldn't allocate memory for initializing array.");
        exit(1);
    }

    m->array = tmp;

    return m;
}


void map_resize(map *m){

    size_t old_capacity = m->capacity;
    m->capacity *= 2;

    node **tmp = calloc(m->capacity, sizeof(node *));
    if(tmp==0){
        fprintf(stderr, "couldn't allocate memory for resizing the map.\n");
        exit(1);
    }

    for(size_t i=0; i<old_capacity; i++){
        node *current = m->array[i];

        while(current!=NULL){
            unsigned long index = hash_function_djb(m, current->key);
            node *new = tmp[index];
            if(new==NULL){
                new = current;
            }
            else{
                while(new->next!=NULL){
                    new = new->next;
                }
                new->next = current;
            }
            current = current->next;
        }
    }

    m->array = tmp;
    return ;
}


void map_add(map *m, const char* key, const void *value, size_t element_size){
    float load_factor = m->count / (float)m->capacity;

    // if load_factor increases , we increase the our capacity so that each bucket gets
    // less elements .
    // but on average we would get amortized O(1) time complexity.
    if(load_factor > 0.5){
        map_resize(m);
    }


    const char* k = strdup(key); // this also allocate memory .

    void *v = malloc(element_size);
    if(v==0){
        fprintf(stderr, "couldn't allocate memory for value\n");
        exit(1);
    }

    // Copying the bytes.
    memcpy(v , value , element_size);

    node *new = malloc(sizeof(node));
    if(new == 0){
        fprintf(stderr, "couldn't allocate memory for creating a new node.\n");
        exit(1);
    }

    new->key = k;
    new->obj = v;
    new->next = 0;

    unsigned long index = hash_function_djb(m, key);

    node *current =  m->array[index];
    if(current==NULL){
        m->array[index] = new;
    }
    else{
        while(current->next!=NULL){
            current = current->next;
        }
        m->array[index] = new;
    }

    m->count++;

    return ;
}


void *map_get(map *m, const char* key){

    unsigned long index = hash_function_djb(m, key);

    node *current = m->array[index];


    while(current!=NULL){
        if(strcmp(current->key, key)==0){
            return current->obj;
        }
        current = current->next;
    }

    // meaning no value found for this key .
    return NULL;
}


void map_set(map *m , const char* key, const void *value, size_t element_size){
    void *v = malloc(element_size);
    if(v==0){
        fprintf(stderr, "Couldn't allocate memory for the value.\n");
        exit(1);
    }

    // Copying the bytes.
    memcpy(v, value, element_size);

    size_t index = hash_function_djb(m, key);

    node *current = m->array[index];
    while(current!=NULL){
        if(strcmp(current->key, key)==0){
            free(current->obj);
            current->obj = v;
            return ;
        }
        current = current->next;
    }

    free(v);
    map_add(m, key, value, element_size);

    return ;
}



void map_free(map *m){
    for(size_t i=0; i<m->capacity; i++){
        node *current = m->array[i];
        while(current!=NULL){
            node *next = current->next;

            free((char *)current->key); // casting it char * , dropping off const
            free(current->obj);
            free(current);

            current = next;
        }
    }
    free(m->array);
    free(m);
}



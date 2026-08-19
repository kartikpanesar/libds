# include <stdio.h>
# include <stdlib.h>

# define MAXWORD 100

typedef struct dl {
    int *items;
    size_t count;
    size_t capacity;
} dl;

void dl_append(dl *nums, int x){

    if(nums->count >= nums->capacity){
        if(nums->count == 0){
            nums->capacity = 2;
        }
        else {
            nums->capacity *= 2;
        }

        int *temp = realloc(nums->items, nums->capacity * sizeof(*(nums->items)));
        if(temp == NULL){
            fprintf(stderr, "couldn't allocate memory for array.\n");
            exit(1);
        }
        else{
            printf("Reallocating memory to a double size.\n");
            nums->items = temp;
        }
    }

    nums->items[nums->count++] = x;
    return ;
}


int main(){

    dl numbers = {0, 0, 0}; // initializing the items pointer.

    for(int j=0; j<1000; j++){
        dl_append(&numbers, j);
    }
    
    for(int j=0; j<numbers.count; j++){
        printf("%d\n", numbers.items[j]);
    }

    return 0;
}


//
// char* get_word(){
//     char c;
//     char word[MAXWORD];
//
//     while((c=getchar())!=EOF){
//         int i = 0;
//         if(c==' ' || c=='\t' || c=='\n'){
//         }
//     }
// }
//


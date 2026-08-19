#ifndef MAP_H 
#define MAP_H

#include <stddef.h>

typedef struct Map map;

map *map_init();

void map_add(map *m, const char* key, const void* value, size_t element_size);
void *map_get(map *m, const char* key);

void map_free(map *m);

#endif

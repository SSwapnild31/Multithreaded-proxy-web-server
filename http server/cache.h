#ifndef CACHE_H
#define CACHE_H

#define MAX_CACHE_SIZE 5

typedef struct cache_node{
    
    char url[1024];
    char *response;
    int size;
    
    struct cache_node *prev;
    struct cache_node *next;
}cache_node;

void cache_init();
cache_node* cache_get(char *url);
void cache_put(char *url, char *response, int size);

#endif
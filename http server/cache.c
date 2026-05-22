#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "cache.h"
#include "lru.h"

cache_node *head = NULL;
cache_node *tail = NULL;

int cache_count = 0;

pthread_mutex_t cache_lock = PTHREAD_MUTEX_INITIALIZER;

void cache_init(){
    head = tail = NULL;
}

cache_node* cache_get(char *url){
    
    pthread_mutex_lock(&cache_lock); 
    
    cache_node *temp = head;

    while(temp){
        if(strcmp(temp->url, url) == 0){
            move_to_front(temp, &head, &tail);
            pthread_mutex_unlock(&cache_lock);
            return temp;
        }
        temp = temp -> next;
    }
    pthread_mutex_unlock(&cache_lock);
    return NULL;
}

void cache_put(char *url, char *response, int size){
    
    pthread_mutex_lock(&cache_lock);

    cache_node *node = malloc(sizeof(cache_node));
    strcpy(node->url, url);
    node->response = malloc(size);

    memcpy(node->response, response, size);
    node->size = size;

    node->prev = NULL;
    node->next = NULL;

    insert_front(node, &head, &tail);
    cache_count++;

    if(cache_count > MAX_CACHE_SIZE){
        remove_tail(&head, &tail);
        cache_count--;
    }

    pthread_mutex_unlock(&cache_lock);
}

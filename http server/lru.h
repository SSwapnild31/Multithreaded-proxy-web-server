#ifndef LRU_H
#define LRU_H

#include "cache.h"

void move_to_front(cache_node *node, cache_node **head, cache_node **tail);
void insert_front(cache_node *node, cache_node **head, cache_node **tail);
void remove_tail(cache_node **head, cache_node **tail);

#endif

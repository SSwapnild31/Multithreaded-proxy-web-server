#include <stdio.h>
#include <stdlib.h>
#include "lru.h"

void insert_front(cache_node *node, cache_node **head, cache_node **tail){

    node->next = *head;
    node->prev = NULL;

    if(*head){
        (*head)->next = node;
    }

    *head = node;

    if(*tail == NULL){
        *tail = node;
    }
}

void move_to_front(cache_node *node, cache_node **head, cache_node **tail){

    if(node == *head) return;

    if(node->prev){
        node->prev->next = node->next;
    }

    if(node->next){
        node->next->prev = node->prev;
    }

    if(node == *tail){
        *tail = node->prev;
    }

    node->prev = NULL;
    node->next = *head;

    (*head)->prev = node;
    *head = node;
}

void remove_tail(cache_node **head, cache_node **tail){

    if(*tail == NULL) return;

    cache_node *temp = *tail;

    if((*tail)->prev){
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }
    else{
        *head = *tail = NULL;
    }

    free(temp->response);
    free(temp);
}

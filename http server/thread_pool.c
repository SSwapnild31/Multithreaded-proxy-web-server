#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "thread_pool.h"
#include "proxy_handler.h"

typedef struct task{
    int client_fd;
    struct task *next;
}task;
task *front = NULL;
task *rear = NULL;

pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

void enqueue(int client_fd)
{
    task *new_task = malloc(sizeof(task));

    new_task->client_fd = client_fd;
    new_task->next = NULL;

    if(rear == NULL){
        front = rear = new_task;
    }
    else{
        rear->next = new_task;
        rear = new_task;
    }
}

int dequeue(){

    if(front == NULL) return -1;

    task *temp = front;

    int client_fd = temp->client_fd;

    front = front->next;

    if(front == NULL){
        rear = NULL;
    }

    free(temp);

    return client_fd;
}

void *worker_thread(void *arg){

    while(1){
        pthread_mutex_lock(&queue_lock);

        while(front == NULL){
            pthread_cond_wait(&queue_cond, &queue_lock);
        }

        int client_fd = dequeue();

        pthread_mutex_unlock(&queue_lock);
        handle_client(client_fd);

        close(client_fd);
    }

    return NULL;
}

void thread_pool_init(int num_threads){

    pthread_t tid;

    for(int i=0; i<num_threads; i++){
        pthread_create(&tid, NULL, worker_thread, NULL);
    }
}

void add_task(int client_fd){

    pthread_mutex_lock(&queue_lock);
    enqueue(client_fd);
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_lock);
}

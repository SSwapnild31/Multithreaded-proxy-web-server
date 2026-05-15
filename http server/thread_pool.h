#ifndef THREAD_POOL_H
#define THREAD_POOL_H

void thread_pool_init(int num_threads);
void add_task(int client_fd);

#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "server.h"
#include "thread_pool.h"

void start_server(int port)
{
    // Create TCP socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        perror("socket");
        exit(1);
    }

    // Reuse address
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Server address structure
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t client_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;  

    // Bind socket to IP + Port
    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("bind");
        exit(1);
    }

    // Listen for clients
    if(listen(server_fd, 10) < 0){
        perror("listen");
        exit(1);
    }

    printf("------------------------------------------\n");
    printf(" Proxy Server Running on Port %d\n",port);
    printf("------------------------------------------\n");

    // Server loop
    while(1){

        // Accept client
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if(client_fd < 0){
            perror("accept");
            continue;
        }

        add_task(client_fd);
    }
}
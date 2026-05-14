#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "proxy_handler.h"
#include "parser.h"
#include "dns_resolver.h"
#include "cache.h"

#define BUFFER_SIZE 4096

void handle_client(int client_fd){

    char buffer[BUFFER_SIZE];

    int bytes = recv(client_fd, buffer, sizeof(buffer)-1, 0);

    if(bytes <= 0){
        return;
    }

    buffer[bytes] = '\0';

    http_request req;

    if(parse_request(buffer, &req) < 0){
        printf("Parse Failed\n");
        return;
    }

    printf("Host: %s\n",req.host);

    cache_node *cached = cache_get(req.path);

    if(cached){
        printf("CACHE HIT\n");
        send(client_fd, cached->response, cached->size, 0);
        return;
    }

    printf("CACHE MISS\n");

    char ip[100];

    if(resolve_hostname(req.host, ip) < 0){
        printf("DNS Failed\n");
        return;
    }

    printf("IP : %s\n",ip);

    int remote_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in remote_addr;
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(80);

    inet_pton(AF_INET, ip, &remote_addr.sin_addr);
    if(connect(remote_fd, &remote_addr, (struct sockaddr*)sizeof(remote_addr)) < 0){
        perror("connect");
        return;
    }

    send(remote_fd, buffer, strlen(buffer), 0);

    char response[BUFFER_SIZE];

    int total = 0;

    while((bytes = recv(remote_fd, response + total, BUFFER_SIZE - total, 0)) > 0){
        total += bytes;
    }

    send(client_fd, response, total, 0);
    cache_put(req.path, response, total);

    close(remote_fd);
}

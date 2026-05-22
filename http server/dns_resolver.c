#include <stdio.h>
#include <netdb.h>
#include "dns_resolver.h"

int resolve_hostname(const char *host, char *ip){
    
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(host, NULL, &hints, &res) != 0){
        return -1;
    }

    struct sockaddr_in *addr = (struct sockaddr_in*)res->ai_addr;

    inet_ntop(AF_INET, &addr->sin_addr, ip, 100);

    freeaddrinfo(res);

    return 0;
}

#include <stdio.h>
#include <string.h>

#include "parser.h"

int parse_request(char *buffer, http_request *req){

    sscanf(buffer,"%s %s",req->method, req->path);

    char *host_ptr = strstr(buffer, "Host:");
    if(host_ptr == NULL){ 
        return -1;
    }

    sscanf(host_ptr,"Host: %s",req->host);

    return 0;
}

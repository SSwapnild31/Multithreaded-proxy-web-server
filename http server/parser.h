#ifndef PARSER_H
#define PARSER_H

typedef struct http_request{
    char method[16];
    char host[256];
    char path[1024];
}http_request;

int parse_request(char *buffer, http_request *req);

#endif

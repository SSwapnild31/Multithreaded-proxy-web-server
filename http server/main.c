#include "cache.h"
#include "thread_pool.h"
#include "server.h"

int main()
{
	cache_init();
	thread_pool_init(4);
	start_server(8080);

	return 0;
}

/*
void start_server(int port)
{
    // Create TCP socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0){
        perror("socket");
        return 1;
    }

    // Reuse address
    int opt = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Server address structure
    struct sockaddr_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;  

    // Bind socket to IP + Port
    if(bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("bind");
        return 1;
    }

    // Listen for clients
    if(listen(sock_fd, 10) < 0){
        perror("listen");
        return 1;
    }

    printf("------------------------------------------\n");
    printf(" Server started & running on port 8080...\n");
    printf("------------------------------------------\n");


    // Server loop
    while(1){

        // Accept client
        int client_fd = accept(sock_fd, NULL, NULL);
        if(client_fd < 0){
            perror("accept");
            continue;
        }

        // Receive HTTp request
        char buffer[1024] = {0};

        int r = recv(client_fd, buffer, sizeof(buffer)-1, 0);        

        if (r <= 0){
            close(client_fd);
            continue;
        }
        
        printf("Request:\n%s\n",buffer);
        printf("------------------------------------------\n");


        // Only supports GET
        if (strncmp(buffer, "GET ", 4) != 0){
            close(client_fd);
            continue;
        }

        // Extract filename
        char *file = buffer + 4;    // GET /index.html HTTP/1.1 -> file -> /index...
        char *end = strchr(file, ' ');  // end ->  HTTP...

        if (end == NULL){
            close(client_fd);
            continue;
        }

        // Adding '\0' to end of the file pointer so we will get only filename like index.html
        *end = '\0';

        // Prevent directory traversal
        if (strstr(file, "..")){
            close(client_fd);
            continue;
        }

        // remove leading '/'
        if (*file == '/') file++;

        // Default file
        //if(strlen(file) == 0)   file = "index.html";

        // Open requested file
        int fd = open(file, O_RDONLY);

        // File not found
        if (fd < 0){
            const char *not_found = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "\r\n"
                "404 File Not Found";

                send(client_fd, not_found, strlen(not_found), 0);

                close(client_fd);
                continue;
        }

        // Get file information
        struct stat st;

        fstat(fd, &st);

        // Detect content type
        const char *type = "text/plain";

        if(strstr(file, ".html"))
            type = "text/html";

        else if(strstr(file, ".css"))
            type = "text/css";

        else if(strstr(file, ".js"))
            type = "application/javascript";

        else if(strstr(file, ".png"))
            type = "image/png";

        else if(strstr(file, ".jpg"))
            type = "image/jpeg";

        // Create HTTP header
        char header[512];

        sprintf(header,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %ld\r\n"
                "\r\n",
                type,
                st.st_size);

        // Send header
        send(client_fd, header, strlen(header), 0);

        // Send file
        off_t offset = 0;
        sendfile(client_fd, fd, &offset, st.st_size);

        // Close descriptors
        close(fd);
        close(client_fd);
    }

    close(sock_fd);
    
    return 0;
}
*/
CC=gcc

CFLAGS=-Wall -pthread

OBJ=main.o server.o thread_pool.o \
    proxy_handler.o parser.o \
    dns_resolver.o cache.o \
    lru.o utils.o

proxy: $(OBJ)
	$(CC) $(OBJ) -o proxy $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o proxy

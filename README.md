# 🌐 Multithreaded HTTP Proxy Web Server with LRU Cache

 A multithreaded HTTP Proxy Web Server built in C using socket programming, pthreads, DNS resolution, and an LRU (Least Recently Used) caching mechanism.

## 📚 Concepts Used:
* Computer Networking
* Socket Programming
* HTTP Protocol
* Multithreading using pthread
* DNS Resolution
* Cache Management
* LRU Eviction Policy
* Linux System Programming

## 📌 Features
* Multithreaded proxy server using pthread
* HTTP request forwarding
* DNS hostname resolution
* LRU cache implementation
* Thread-safe cache handling using mutex
* Modular project architecture
* HTTP request parsing
* Client-server communication using TCP sockets

## 📂 Project Structure
```text
proxy_project/
│
├── main.c
├── server.c
├── server.h
│
├── thread_pool.c
├── thread_pool.h
│
├── proxy_handler.c
├── proxy_handler.h
│
├── parser.c
├── parser.h
│
├── dns_resolver.c
├── dns_resolver.h
│
├── cache.c
├── cache.h
│
├── lru.c
├── lru.h
│
├── utils.c
├── utils.h
│
└── Makefile
```

## 💾 Working Flow
```text
Browser
   ↓
Proxy Server
   ↓
Cache Lookup
   ↓
(Cache Hit) → Return Cached Response
   ↓
(Cache Miss)
   ↓
DNS Resolution
   ↓
Remote Web Server
   ↓
Fetch Response
   ↓
Store in LRU Cache
   ↓
Send Response to Browser
```

## ➡️ File Descriptions

## 🚀 `main.c`
Entry point of the proxy server.

### Responsibilities:
* Initialize cache
* Initialize thread pool
* Start proxy server


## 🌐 `server.c` / `server.h`
Handles all server-side socket operations.

### Responsibilities:
* Create socket
* Bind socket to port
* Listen for incoming clients
* Accept client connections
* Send client requests to worker threads


## 🧵 `thread_pool.c` / `thread_pool.h`
Implements multithreading using pthreads.

### Responsibilities:
* Create worker threads
* Manage task queue
* Synchronize threads using mutex and condition variables
* Handle concurrent client requests


## 📨 `proxy_handler.c` / `proxy_handler.h`
Core proxy logic implementation.

### Responsibilities:
* Receive browser requests
* Parse HTTP requests
* Check cache
* Connect to remote servers
* Fetch responses
* Return responses to clients


## 🔍 `parser.c` / `parser.h`
Parses incoming HTTP requests.

### Responsibilities:
* Extract HTTP method
* Extract host name
* Extract requested path
* Process request headers


## 🌎 `dns_resolver.c` / `dns_resolver.h`
Handles DNS resolution.

### Responsibilities:
* Convert domain names into IP addresses
* Use `getaddrinfo()` for hostname lookup
* Resolve remote server addresses


## 🗂️ `cache.c` / `cache.h`
Manages proxy cache operations.

### Responsibilities:
* Store server responses
* Retrieve cached responses
* Thread-safe cache access
* Cache insertion and lookup


## ⚡ `lru.c` / `lru.h`
Implements the LRU (Least Recently Used) cache policy.

### Responsibilities:
* Maintain doubly linked list
* Move recently accessed items to front
* Remove least recently used items
* Cache eviction management


## 🛠️ `utils.c` / `utils.h`
Contains helper utility functions.

### Responsibilities:
* Logging
* Error handling
* Common reusable helper functions


## ⚙️ `Makefile`
Automates project compilation.

### Responsibilities:
* Compile source files
* Generate object files
* Link executable
* Clean build files

### Commands:
```bash id="v9myh0"
$ make
$ make clean
```


# 🧠 Overall Architecture
```text id="4l20t0"
Browser
   ↓
HTTP Proxy Server
   ↓
Thread Pool
   ↓
Request Parser
   ↓
LRU Cache
   ↓
DNS Resolver
   ↓
Remote Web Server
```


## ✒️ Technologies Used
* C Programming
* POSIX Socket API
* pthread Library
* TCP/IP Networking
* DNS Resolution using getaddrinfo()
* Makefile


## ▶️ Build Instructions
### Compile
```bash
$ make
```

or

```bash
$ gcc *.c -o proxy -pthread
```

### Run
```bash
$ ./proxy
```


## 🌐 Configure Browser Proxy
Set browser proxy configuration:
```text
HTTP Proxy : 127.0.0.1
Port       : 8080
```

Then open:
```text
http://neverssl.com
```


## 🎟️ LRU Cache
The proxy server uses an LRU (Least Recently Used) cache to improve performance by storing previously fetched responses.

## Cache Operations
* Cache Hit
  * Return cached response immediately
  * Move cache node to front

* Cache Miss
  * Fetch response from remote server
  * Store response in cache
  * Remove least recently used entry if cache is full


## 🛢️ Thread Pool
The server uses a thread pool architecture:

* Main thread accepts client connections
* Worker threads process requests concurrently
* Mutex and condition variables ensure synchronization


## 🌠 Supported Features
* HTTP Proxying
* Concurrent Client Handling
* DNS Lookup
* Response Caching
* TCP Socket Communication


## 🚀 Future Improvements
* HTTPS CONNECT Support
* epoll-based scalable I/O
* Dynamic memory buffering
* Full HTTP header parsing
* HashMap-based O(1) cache lookup
* Logging system
* Cache expiration mechanism
* Chunked transfer encoding support


## 📖 Learning Outcomes
This project helps understand:
* Low-level networking
* Concurrent programming
* Proxy server architecture
* Cache systems
* Linux networking internals
* System design fundamentals

## 🤝 Contribution
Feel free to fork and improve this project.

## 📜 License
This project is for learning purposes.

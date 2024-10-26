# Socket_Network_Cpp

ok, Here an explaination for every Function we used ....

### Server Code Functions

1. **`socket()`**
   - **Prototype**: `int socket(int domain, int type, int protocol);`
   - **Description**: Creates a new socket and returns a file descriptor. The parameters specify the protocol family (e.g., `AF_INET` for IPv4), the socket type (e.g., `SOCK_STREAM` for TCP), and the protocol (usually set to 0 to select the default protocol).
   - **Example**: `int server_fd = socket(AF_INET, SOCK_STREAM, 0);`

2. **`setsockopt()`**
   - **Prototype**: `int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);`
   - **Description**: Configures socket options. Here, it’s used to allow the socket to reuse the address, which is useful when restarting the server without waiting for the socket to be released.
   - **Example**: `setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));`

3. **`bind()`**
   - **Prototype**: `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
   - **Description**: Associates the socket with a specific IP address and port number. This is necessary for the server to listen for incoming connections on that address and port.
   - **Example**: `bind(server_fd, (struct sockaddr *)&address, sizeof(address));`

4. **`listen()`**
   - **Prototype**: `int listen(int sockfd, int backlog);`
   - **Description**: Marks the socket as a passive socket that will be used to accept incoming connection requests. The `backlog` parameter specifies the maximum length of the queue of pending connections.
   - **Example**: `listen(server_fd, 3);`

5. **`accept()`**
   - **Prototype**: `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`
   - **Description**: Blocks the server until a client connects. It creates a new socket for the connection. The client's address can be retrieved if needed.
   - **Example**: `new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);`

6. **`recv()`**
   - **Prototype**: `ssize_t recv(int sockfd, void *buf, size_t len, int flags);`
   - **Description**: Receives data from a connected socket. It fills the provided buffer with incoming data and returns the number of bytes received.
   - **Example**: `recv(new_socket, buffer, sizeof(buffer), 0);`

7. **`send()`**
   - **Prototype**: `ssize_t send(int sockfd, const void *buf, size_t len, int flags);`
   - **Description**: Sends data over a connected socket. The data to be sent is specified in the buffer.
   - **Example**: `send(new_socket, message.c_str(), message.length(), 0);`

8. **`close()`**
   - **Prototype**: `int close(int fd);`
   - **Description**: Closes a socket file descriptor, releasing any resources associated with it. It should be called when done using a socket.
   - **Example**: `close(new_socket);` and `close(server_fd);`

### Client Code Functions

1. **`socket()`**
   - Similar to the server, this creates a new socket for the client to communicate with the server.

2. **`inet_pton()`**
   - **Prototype**: `int inet_pton(int af, const char *src, void *dst);`
   - **Description**: Converts an IP address in text format (e.g., "127.0.0.1") to binary form. This is necessary for the `sockaddr_in` structure used in socket communication.
   - **Example**: `inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);`

3. **`connect()`**
   - **Prototype**: `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
   - **Description**: Initiates a connection to the server using the specified address and port. The client must successfully connect to send or receive data.
   - **Example**: `connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));`

4. **`send()`**
   - Similar to the server, this sends data from the client to the server.

5. **`recv()`**
   - Similar to the server, this receives data sent from the server to the client.

6. **`close()`**
   - Similar to the server, this closes the client socket when communication is done.

### Summary

We build it like it a chat every message the other side should response with one too...

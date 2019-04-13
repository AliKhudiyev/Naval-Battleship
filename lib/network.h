
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#ifndef NETWORK
#define NETWORK

#define PORT    4543

#define INIT_ALL_SERVER_ESSENTIALS(network)                                        \
    network.sock_fd =  socket(AF_INET, SOCK_STREAM, 0);                            \
    if (network.sock_fd < 0) perror("ERROR opening socket");                       \
    bzero((char *) &network.server_addr, sizeof(network.server_addr));             \
    network.port=PORT;                                                             \
    network.server_addr.sin_family = AF_INET;                                      \
    network.server_addr.sin_addr.s_addr = INADDR_ANY;                              \
    network.server_addr.sin_port = htons(network.port);                            \
    if (bind(network.sock_fd, (struct sockaddr *) &network.server_addr,            \
        sizeof(network.server_addr)) < 0) perror("ERROR on binding");              \
    listen(network.sock_fd, 2);                                                    \
    network.client_len = sizeof(network.client_addr);                              \
    network.new_sock_fd = accept(network.sock_fd,                                  \
                 (struct sockaddr *) &network.client_addr, &network.client_len);   \
    if (network.new_sock_fd < 0) perror("ERROR on accept");                        \
    printf("network.server: got connection from %s port %d\n",                     \
        inet_ntoa(network.client_addr.sin_addr), ntohs(network.client_addr.sin_port));

#define INIT_ALL_CLIENT_ESSENTIALS(network, ip)                         \
    network.port = PORT;                                                \
    network.sock_fd = socket(AF_INET, SOCK_STREAM, 0);                  \
    if (network.sock_fd < 0) perror("ERROR opening socket");            \
    network.server = gethostbyname(ip);                                 \
    if (network.server == NULL) {                                       \
        fprintf(stderr,"ERROR, no such host\n");                        \
        exit(0);                                                        \
    }                                                                   \
    bzero((char *) &network.server_addr, sizeof(network.server_addr));  \
    network.server_addr.sin_family = AF_INET;                           \
    bcopy((char *)network.server->h_addr,                               \
         (char *)&network.server_addr.sin_addr.s_addr,                  \
         network.server->h_length);                                     \
    network.server_addr.sin_port = htons(network.port);                 \
    if (connect(network.sock_fd, (struct sockaddr *) &network.server_addr, sizeof(network.server_addr)) < 0) perror("ERROR connecting");

struct Network{
    int sock_fd, new_sock_fd, port;
    socklen_t client_len;
    struct sockaddr_in server_addr, client_addr;
    struct hostent* server=nullptr;
    char* ip_addr;

    static ssize_t send_package(int fd, const void* buf, size_t n_bytes, int flags=0){
        send(fd, buf, n_bytes, flags);
    }
    static ssize_t receive_package(int fd, void* buf, size_t n_bytes){
        read(fd, buf, n_bytes);
    }
    ~Network(){
        server=nullptr;
    }
};

#endif

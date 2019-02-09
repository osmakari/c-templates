#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>

struct client {
    int socket;
    struct sockaddr_in sockaddr;
};

struct server {
    uint16_t max_clients;
    struct client **__CLIENTS;
    uint16_t port;
    int _sockfd;
    struct sockaddr_in sockaddr;
};

#endif
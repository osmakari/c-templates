#include <stdio.h>
#include <unistd.h>
#include "server.h"

struct server *server_create (uint16_t port, uint16_t max_clients) {
    struct server *s = (struct server *)malloc(sizeof(struct server));
    s->max_clients = max_clients;
    s->port = port;

    s->_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (s->_sockfd == -1) {
        free(s);
        return NULL;
    }
    int enable = 1;
    setsockopt(s->_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    s->sockaddr.sin_family = AF_INET;
    s->sockaddr.sin_addr.s_addr = INADDR_ANY;
    s->sockaddr.sin_port = s->port;

    if(bind(s->_sockfd, (struct sockaddr *)&s->sockaddr, sizeof(s->sockaddr)) < 0) {
        free(s);
        return NULL;
    }

    listen(s->_sockfd, 3);

    s->__CLIENTS = (struct client **)malloc(sizeof(struct client*) * max_clients);

    return s;
}

int server_update (struct server *_server) {
    int client_sock, c, read_size;
    char client_message[2000];
    struct sockaddr_in client;
    c = sizeof(struct sockaddr_in);

    client_sock = accept(_server->_sockfd, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0) {
        return 0;
    }

    while((read_size = read(client_sock, client_message, sizeof(client_message))) > 0) {
        write(client_sock , client_message , strlen(client_message));
        memset( &client_message, 0, sizeof(client_message));
    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
}
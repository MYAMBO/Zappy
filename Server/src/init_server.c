/*
** EPITECH PROJECT, 2025
** init_server.c
** File description:
** init_server.c
** created and edited by antoiix.
** All rights reserved
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"
#include "garbage.h"

int init_server_fields(server_t *server)
{
    server->port = port;
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server->poll_list = NULL;
    server->poll_count = 0;
    if (server->server_fd == -1)
        return FAILURE;
    return SUCCESS;
}

int init_server(server_t *server, long port)
{
    int bind_value;
    struct sockaddr_in my_addr;

    if (init_server_fields(server) == FAILURE)
        return FAILURE;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_value = bind(server->server_fd,
        (struct sockaddr*)(&my_addr), sizeof(my_addr));
    if (bind_value == -1)
        return FAILURE;
    if (listen(server->server_fd, 10) == -1)
        return FAILURE;
    if (append_node_poll_handling(&server->poll_list,
        server->server_fd, false) == FAILURE)
        return FAILURE;
    server->poll_count++;
    return SUCCESS;
}

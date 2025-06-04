/*
** EPITECH PROJECT, 2025
** handle_event.c
** File description:
** handle_event.c
** created and edited by antoiix.
** All rights reserved
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include <arpa/inet.h>
#include <unistd.h>

int create_new_connection(server_t* server)
{
    struct sockaddr_in peer_addr;
    socklen_t addr_len = sizeof(peer_addr);
    int client_fd = accept(server->server_fd, (struct sockaddr*)(&peer_addr), &addr_len);

    if (client_fd == -1)
        return FAILURE;
    if (append_node_poll_handling(&server->poll_list, client_fd) == FAILURE)
        return FAILURE;
    if (write(client_fd, "Welcome to Zappy\n", 17) < 0)
        return FAILURE;
    server->poll_count++;
    return SUCCESS;
}

int handle_connection(server_t* server, struct pollfd poll)
{
    if (poll.revents & POLLIN && poll.fd == server->server_fd)
    {
        if (create_new_connection(server) == 84)
            return FAILURE;
        return 1;
    }
    return SUCCESS;
}

// BE CAREFUL BUFFER LIMITED TO 1024 !
int handle_command(server_t* server, struct pollfd poll)
{
    char buffer[1024] = {0};

    if (poll.revents & POLLIN)
    {
        ssize_t bytes_read = read(poll.fd, buffer, 1023);

        buffer[bytes_read] = '\0';
        if (bytes_read < 0) {
            perror("read failed");
            remove_node_poll_handling(&server->poll_list, poll.fd);
            close(poll.fd);
            server->poll_count--;
            return FAILURE;
        }
        if (bytes_read == 0)
        {
            close(poll.fd);
            remove_node_poll_handling(&server->poll_list, poll.fd);
            server->poll_count--;
            return FAILURE;
        }
        if (strncmp(buffer, "quit", 4) == 0)
        {
            close(poll.fd);
            remove_node_poll_handling(&server->poll_list, poll.fd);
            server->poll_count--;
            return SUCCESS;
        }
    }
    return SUCCESS;
}

int handle_event(server_t* server)
{
    int val_connection;

    for (poll_handling_t *node = server->poll_list; node != NULL; node = node->next)
    {
        val_connection = handle_connection(server, node->poll_fd);
        if (val_connection == FAILURE)
            return FAILURE;
        if (val_connection == 1)
            continue;
        val_connection = handle_command(server, node->poll_fd);
        if (val_connection == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

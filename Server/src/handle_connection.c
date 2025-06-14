/*
** EPITECH PROJECT, 2025
** handle_connection.c
** File description:
** handle_connection.c
** created and edited by antoiix.
** All rights reserved
*/

#include "handle_connection.h"

static int send_message_connection(int client_fd)
{
    char *message = my_malloc(sizeof(char) * 1024);

    if (message == NULL)
        return FAILURE;
    sprintf(message, "Client connected with local fd : %d", client_fd);
    logger_info(message, FILE_OUTPUT, true);
    my_free(message);
    return SUCCESS;
}

int create_new_connection(server_t *server)
{
    struct sockaddr_in peer_addr;
    socklen_t addr_len = sizeof(peer_addr);
    int client_fd = accept(server->server_fd,
        (struct sockaddr*)(&peer_addr), &addr_len);

    if (client_fd == -1)
        return FAILURE;
    if (append_node_poll_handling(&server->poll_list, client_fd,
        true) == FAILURE)
        return FAILURE;
    if (write(client_fd, "WELCOME\n", 8) < 0)
        return FAILURE;
    server->poll_count++;
    if (send_message_connection(client_fd) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int handle_connection(server_t *server, pollfd_t poll)
{
    if (poll.revents & POLLIN && poll.fd == server->server_fd) {
        if (create_new_connection(server) == 84)
            return FAILURE;
        return 1;
    }
    return SUCCESS;
}

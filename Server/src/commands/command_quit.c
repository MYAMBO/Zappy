/*
** EPITECH PROJECT, 2025
** command_quit.c
** File description:
** command_quit.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>

#include "commands.h"
#include "garbage.h"
#include "logger.h"
#include "server.h"

int quit_command(server_t *server, poll_handling_t *node)
{
    char *message = my_malloc(sizeof(char) * 1024);

    if (message == NULL)
        return FAILURE;
    sprintf(message, "Quit command executed by client with id"
        " : %d, local fd : %d", node->player->id, node->poll_fd.fd);
    logger_info(message, FILE_OUTPUT, true);
    my_free(message);
    close(node->poll_fd.fd);
    remove_node_poll_handling(&server->poll_list, node->poll_fd.fd);
    server->poll_count--;
    return FAILURE;
}

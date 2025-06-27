/*
** EPITECH PROJECT, 2025
** command_look.c
** File description:
** command_look.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "commands.h"
#include "look_around_communication.h"
#include "utils.h"

int look_command(server_t *server, poll_handling_t *node, char **args)
{
    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    char *str = player_looks_around(node->player, server->poll_list, server->map);
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    return SUCCESS;
}

/*
** EPITECH PROJECT, 2025
** command_eject.c
** File description:
** command_eject.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "commands.h"
#include "eject_communication.h"
#include "utils.h"

int eject_command(server_t *server, poll_handling_t *node, char **args)
{
    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    char *str = eject_player(node->player, server->poll_list, server->map);
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    return SUCCESS;
}
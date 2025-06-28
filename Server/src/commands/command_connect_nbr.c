/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** command_connect_nbr
*/

#include "commands.h"
#include "utils.h"
#include "actions_communication.h"
#include "unistd.h"

int connect_nbr_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;

    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    str = get_slot_remaining(node->player, server);
    if (!str)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    return SUCCESS;
}
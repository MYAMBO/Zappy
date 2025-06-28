/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** drop_command
*/

#include "commands.h"
#include "utils.h"
#include "actions_communication.h"
#include "unistd.h"

int drop_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;

    if (array_len(args) != 2) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    str = can_player_drops_items(node->player, server->map, args[1], server);
    if (!str)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    return SUCCESS;
}

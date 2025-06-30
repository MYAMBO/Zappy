/*
** EPITECH PROJECT, 2025
** command_broadcast.c
** File description:
** command_broadcast.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "actions_communication.h"
#include "actions_protocol.h"
#include "commands.h"
#include "utils.h"

int broadcast_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str;

    if (array_len(args) != 2) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    if (player_plays_broadcast(node->player, args[1], server) == NULL)
        return FAILURE;
    str = player_broadcast(node->player, args[1]);
    if (send_message_graphic(server, str) == FAILURE)
        return FAILURE;
    write(node->poll_fd.fd, "ok\n", 3);
    return SUCCESS;
}

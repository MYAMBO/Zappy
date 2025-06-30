/*
** EPITECH PROJECT, 2025
** command_left.c
** File description:
** command_left.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "server.h"
#include "commands.h"
#include "movements_communication.h"
#include "player_informations_protocol.h"
#include "utils.h"

int left_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;

    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    player_turns_left(node->player);
    str = get_player_position(node->player);
    if (!str)
        return FAILURE;
    if (send_message_graphic(server, str) == FAILURE)
        return FAILURE;
    write(node->poll_fd.fd, "ok\n", 3);
    return SUCCESS;
}

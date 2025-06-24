/*
** EPITECH PROJECT, 2025
** command_right.c
** File description:
** command_right.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "server.h"
#include "commands.h"
#include "movements_communication.h"
#include "utils.h"

int right_command(server_t *server, poll_handling_t *node, char **args)
{
    (void)server;
    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    player_turns_right(node->player);
    write(node->poll_fd.fd, "ok\n", 3);
    return SUCCESS;
}

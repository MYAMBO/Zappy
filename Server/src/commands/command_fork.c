/*
** EPITECH PROJECT, 2025
** command_fork.c
** File description:
** command_fork.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "actions_protocol.h"
#include "commands.h"
#include "eject_communication.h"
#include "handle_fork_communication.h"
#include "player_informations_protocol.h"
#include "utils.h"

int fork_command(server_t *server, poll_handling_t *node, char **args)
{
    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    if (handle_fork_action(node->player, server) == NULL)
        return FAILURE;
    write(node->poll_fd.fd, "ok\n", 3);
    return SUCCESS;
}

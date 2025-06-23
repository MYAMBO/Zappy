/*
** EPITECH PROJECT, 2025
** command_forward.c
** File description:
** command_forward.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "commands.h"
#include "garbage.h"
#include "movements_communication.h"
#include "utils.h"

int forward_command(server_t *server, poll_handling_t *node, char **args)
{
    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    handle_forward_action(node->player, server);
    write(node->poll_fd.fd, "ok\n", 3);
    return SUCCESS;
}

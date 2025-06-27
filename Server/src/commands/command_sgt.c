/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** command_sgt
*/

#include "commands.h"
#include "utils.h"
#include "time_unit_protocol.h"
#include "unistd.h"

int sgt_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;

    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    str = time_unit_request(server);
    if (!str)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    return SUCCESS;
}

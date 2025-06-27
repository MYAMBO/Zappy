/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** command_sst
*/

#include "commands.h"
#include "utils.h"
#include "time_unit_protocol.h"
#include "unistd.h"

int sst_command(server_t *server, poll_handling_t *node, char **args)
{
    int nb = 0;
    char *str = NULL;

    if (array_len(args) != 2) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    nb = atoi(args[1]);
    if (nb <= 0){
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    str = time_unit_modification(server, nb);
    if (!str)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    return SUCCESS;
}
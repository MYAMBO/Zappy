/*
** EPITECH PROJECT, 2025
** command_msz.c
** File description:
** command_msz.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "commands.h"
#include "map_protocol.h"
#include "utils.h"

int msz_command(server_t *server, poll_handling_t *node, char **args)
{
    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    char *str = get_map_size(server);
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    return SUCCESS;
}

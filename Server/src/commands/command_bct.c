/*
** EPITECH PROJECT, 2025
** command_bct.c
** File description:
** command_bct.c
** created and edited by antoiix.
** All rights reserved
*/

#include <stdlib.h>
#include <unistd.h>
#include "commands.h"
#include "map_protocol.h"
#include "utils.h"

static int send_bct_command(server_t *server,
    poll_handling_t *node, char **args)
{
    long int x = 0;
    long int y = 0;
    char *str;
    char *bad_x;
    char *bad_y;

    x = strtol(args[1], &bad_x, 10);
    y = strtol(args[2], &bad_y, 10);
    if (bad_x == args[1] || bad_y == args[2]) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    str = get_tile_content(server->map, (int)x, (int)y);
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    return SUCCESS;
}

int bct_command(server_t *server, poll_handling_t *node, char **args)
{
    if (args == NULL)
        return FAILURE;
    if (array_len(args) != 3) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    return send_bct_command(server, node, args);
}

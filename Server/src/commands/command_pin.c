/*
** EPITECH PROJECT, 2025
** command_pin.c
** File description:
** command_pin.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "commands.h"
#include "player_informations_protocol.h"
#include "utils.h"

static int send_pin_command(server_t *server,
    poll_handling_t *node, char **args)
{
    poll_handling_t *tmp;
    int id = 0;
    char *str;

    id = atoi(args[1] + 1);
    tmp = search_player_node(id, server);
    if (tmp == NULL) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    str = get_player_inventory(tmp->player, tmp->player->x, tmp->player->y);
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    return SUCCESS;
}

int pin_command(server_t *server, poll_handling_t *node, char **args)
{
    if (args == NULL)
        return FAILURE;
    if (array_len(args) != 2 || strlen(args[1]) < 2 ||
        args[1][0] != '#') {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    return send_pin_command(server, node, args);
}

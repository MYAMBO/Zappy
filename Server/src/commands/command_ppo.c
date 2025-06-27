/*
** EPITECH PROJECT, 2025
** command_ppo.c
** File description:
** command_ppo.c
** created and edited by antoiix.
** All rights reserved
*/

#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "garbage.h"
#include "player_informations_protocol.h"
#include "server.h"
#include "utils.h"

static int send_ppo_command(server_t *server,
                            poll_handling_t *node, char **args)
{
    poll_handling_t *tmp;
    long int id = 0;
    char *str;
    char *bad;

    id = strtol(args[1] + 1, &bad, 10);
    tmp = search_player_node((int)id, server);
    if (tmp == NULL || bad == args[1] + 1) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    str = get_player_position(tmp->player);
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    return SUCCESS;
}

int ppo_command(server_t *server, poll_handling_t *node, char **args)
{
    if (args == NULL)
        return FAILURE;
    if (array_len(args) != 2 || strlen(args[1]) < 2 ||
        args[1][0] != '#') {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
        }
    return send_ppo_command(server, node, args);
}
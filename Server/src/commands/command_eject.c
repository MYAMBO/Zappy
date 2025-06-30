/*
** EPITECH PROJECT, 2025
** command_eject.c
** File description:
** command_eject.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>

#include "actions_protocol.h"
#include "commands.h"
#include "eject_communication.h"
#include "player_informations_protocol.h"
#include "utils.h"

int eject_command(server_t *server, poll_handling_t *node, char **args)
{
    char *tmp;
    char *str;

    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    str = eject_player(node->player, server->poll_list, server->map, server);
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    if (strcmp(str, "ko\n") != 0) {
        tmp = player_expulsion(node->player);
        if (tmp == NULL)
            return FAILURE;
        if (send_message_graphic(server, tmp) == FAILURE)
            return FAILURE;
        my_free(tmp);
    }
    my_free(str);
    return SUCCESS;
}

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** command_tna
*/

#include "utils.h"
#include "unistd.h"
#include "commands.h"
#include "player_informations_protocol.h"


int tna_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;

    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "sbp\n", 4);
        return SUCCESS;
    }
    str = get_team_names(server);
    if (!str)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    return SUCCESS;
}

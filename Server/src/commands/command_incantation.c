/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** command_incantation
*/

#include "commands.h"
#include "utils.h"
#include "incantation_communication.h"
#include "unistd.h"

int incantation_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;

    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    str = start_incantation(node->player, server, server->map);
    if (!str)
        return FAILURE;
    if (strcmp(str, "ko\n") == 0)
        write(node->poll_fd.fd, str, strlen(str));
    return SUCCESS;
}

int end_incantation_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;

    (void)node;
    (void)args;
    str = end_incantation(server, server->map);
    printf("lala1\n");
    if (!str)
        return FAILURE;
    printf("lala2\n");
    printf("%s", str);
    for (poll_handling_t *poll = server->poll_list; poll != NULL; poll = poll->next) {
        if (!poll->player || strcmp(poll->player->team_name, "GRAPHIC") == 0)
            continue;
        if (poll->player->in_incantation == server->incantation_list[0].incantation_nb &&
            strcmp(str, "ko\n") == 0) {
            poll->player->in_incantation = -1;
            write(poll->player->fd, str, strlen(str));
        }
        if (poll->player->in_incantation == server->incantation_list[0].incantation_nb &&
            strcmp(str, "ko\n") != 0)
        {
            poll->player->in_incantation = -1;
            poll->player->level++;
            write(poll->player->fd, str, strlen(str));
        }
    }
    return SUCCESS;
}
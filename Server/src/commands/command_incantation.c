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
    str = start_incantation(node->player, node, server->map);
    if (!str)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));



    if (strcmp(str, "ko\n") != 0){
        for (poll_handling_t *poll = node; poll != NULL; poll = poll->next){
            if (poll->player->in_incantation){
                poll->player->in_incantation = false;
                poll->player->level++;
            }
        }
    }



    return SUCCESS;
}

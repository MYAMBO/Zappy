/*
** EPITECH PROJECT, 2025
** utils.c
** File description:
** utils.c
** created and edited by antoiix.
** All rights reserved
*/

#include "utils.h"

#include <unistd.h>

#include "server.h"

poll_handling_t *search_player_node(int id, server_t *server)
{
    if (server == NULL)
        return NULL;
    for (poll_handling_t *tmp = server->poll_list; tmp != NULL;
        tmp = tmp->next) {
        if (tmp->player == NULL || tmp->player->team_name == NULL ||
            strcmp(tmp->player->team_name, "GRAPHIC") == 0 ||
            !tmp->player->connected)
            continue;
        if (tmp->player->id == id)
            return tmp;
    }
    return NULL;
}

int send_message_graphic(server_t *server, char *message)
{
    if (server == NULL || message == NULL)
        return FAILURE;
    for (poll_handling_t *tmp = server->poll_list;
        tmp != NULL; tmp = tmp->next) {
        if (tmp->player == NULL || tmp->player->team_name == NULL ||
            !tmp->player->connected)
            continue;
        if (strcmp(tmp->player->team_name, "GRAPHIC") == 0) {
            write(tmp->poll_fd.fd, message, strlen(message));
            break;
        }
    }
    return SUCCESS;
}

int array_len(char **arr)
{
    int i = 0;

    if (arr == NULL)
        return 0;
    for (; arr[i] != NULL; i++);
    return i;
}

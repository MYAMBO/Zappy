/*
** EPITECH PROJECT, 2025
** graphic_connect.c
** File description:
** graphic_connect.c
** created and edited by antoiix.
** All rights reserved
*/

#include "graphic_connect.h"

bool is_graphic_user(server_t *server, poll_handling_t *node)
{
    slot_table_t *table;

    if (server == NULL || node == NULL || server->team_names == NULL
        || server->team_names[0] == NULL)
        return false;
    table = server->team_names[0];
    for (slot_t *tmp = table->slots; tmp; tmp = tmp->next) {
        if (tmp->id_user == node->player->id)
            return true;
    }
    return false;
}

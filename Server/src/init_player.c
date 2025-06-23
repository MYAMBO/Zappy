/*
** EPITECH PROJECT, 2025
** init_player.c
** File description:
** init_player.c
** created and edited by antoiix.
** All rights reserved
*/

#include "init_player.h"
#include "unique_connection_id_getter.h"
#include <stdlib.h>
#include <string.h>

#include "garbage.h"
#include "struct.h"

void init_resources(ai_stats_t *new_tmp)
{
    new_tmp->life = 1260;
    new_tmp->nb_deraumere = 0;
    new_tmp->nb_linemate = 0;
    new_tmp->nb_mendiane = 0;
    new_tmp->nb_phiras = 0;
    new_tmp->nb_sibur = 0;
    new_tmp->nb_thystame = 0;
}

ai_stats_t *init_new_player(int fd, int x, int y, char *team_name)
{
    ai_stats_t *new_tmp = my_malloc(sizeof(ai_stats_t));

    if (new_tmp == NULL)
        return NULL;
    new_tmp->connected = false;
    new_tmp->fd = fd;
    new_tmp->direction = 0;
    new_tmp->id = get_unique_connection_id();
    new_tmp->in_incantation = false;
    new_tmp->level = 1;
    new_tmp->tmp_command = NULL;
    new_tmp->team_name = my_malloc(sizeof(char) * (strlen(team_name) + 1));
    if (new_tmp->team_name == NULL)
        return NULL;
    strcat(new_tmp->team_name, team_name);
    memset(new_tmp->team_name, 0, sizeof(char) * strlen(team_name));
    new_tmp->x = x;
    new_tmp->y = y;
    init_resources(new_tmp);
    return new_tmp;
}

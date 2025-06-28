/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** player_connection_protocol
*/


#include "player_connection_protocol.h"

static int choose_direction(ai_stats_t *ai)
{
    if (ai->direction == NORTH)
        return 1;
    if (ai->direction == EAST)
        return 2;
    if (ai->direction == SOUTH)
        return 3;
    if (ai->direction == WEST)
        return 4;
    return 0;
}

char *player_new_connection(ai_stats_t *ai)
{
    int direction = choose_direction(ai);
    int alloc = 0;
    char *result = NULL;

    alloc = snprintf(NULL, 0, "pnw #%d %d %d %d %d %s\n",
        ai->id, ai->x, ai->y, direction, ai->level, ai->team_name);
    result = my_malloc(alloc + 1);
    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pnw #%d %d %d %d %d %s\n",
             ai->id, ai->x, ai->y, direction, ai->level, ai->team_name);
    return result;
}

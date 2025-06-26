/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** player_informations_protocol
*/

#include "player_informations_protocol.h"

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

char *get_player_position(ai_stats_t *ai)
{
    int direction = choose_direction(ai);
    int alloc = 0;
    char *result = NULL;

    alloc = snprintf(NULL, 0, "ppo #%d %d %d %d\n",
        ai->id, ai->x, ai->y, direction);
    result = my_malloc(alloc + 1);
    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "ppo #%d %d %d %d\n",
        ai->id, ai->x, ai->y, direction);
    return result;
}

char *get_player_level(ai_stats_t *ai)
{
    int alloc = snprintf(NULL, 0, "plv #%d %d\n", ai->id, ai->level);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "plv #%d %d\n", ai->id, ai->level);
    return result;
}

static char *return_player_resources(ai_stats_t *ai, int alloc, int x, int y)
{
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1,
        "pin #%d %d %d %d %d %d %d %d %d %d\n", ai->id, x, y,
        ai->inventory.resources[0],
        ai->inventory.resources[1],
        ai->inventory.resources[2],
        ai->inventory.resources[3],
        ai->inventory.resources[4],
        ai->inventory.resources[5],
        ai->inventory.resources[6]);
    return result;
}

char *get_player_inventory(ai_stats_t *ai, int x, int y)
{
    int alloc = snprintf(NULL, 0,
                    "pin #%d %d %d %d %d %d %d %d %d %d\n", ai->id, x, y,
                    ai->inventory.resources[0],
                    ai->inventory.resources[1],
                    ai->inventory.resources[2],
                    ai->inventory.resources[3],
                    ai->inventory.resources[4],
                    ai->inventory.resources[5],
                    ai->inventory.resources[6]);

    return return_player_resources(ai, alloc, x, y);
}

char *end_of_game(ai_stats_t *ai)
{
    int alloc = snprintf(NULL, 0, "seg %s\n", ai->team_name);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "seg %s\n", ai->team_name);
    return result;
}

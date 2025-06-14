/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** player_informations_protocol
*/

#include "player_informations_protocol.h"

char *get_teams_name(server_t *server)
{
    int total_len = 0;
    char *result = NULL;
    char *buffer = NULL;

    for (int i = 0; server->team_names[i] != NULL; i++)
        total_len += snprintf(NULL, 0, "tna %s\n", server->team_names[i]);
    result = my_malloc(total_len + 1);
    if (!result)
        return NULL;
    buffer = my_malloc(total_len + 1);
    if (!buffer)
        return NULL;
    result[0] = '\0';
    for (int i = 0; server->team_names[i]; i++) {
        snprintf(buffer, total_len + 1, "tna %s\n", server->team_names[i]);
        strcat(result, buffer);
    }
    //my_free needed here for buffer
    return result;
}

char *get_player_position(ai_stats_t ai)
{
    int alloc = snprintf(NULL, 0, "ppo #%d %d %d\n", ai.id, ai.x, ai.y);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "ppo #%d %d %d\n", ai.id, ai.x, ai.y);
    return result;
}

char *get_player_level(ai_stats_t ai)
{
    int alloc = snprintf(NULL, 0, "plv #%d %d\n", ai.id, ai.level);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "plv #%d %d\n", ai.id, ai.level);
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

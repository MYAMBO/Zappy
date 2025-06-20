/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** actions_protocol
*/


#include "actions_protocol.h"

char *player_expulsion(ai_stats_t *ai)
{
    int alloc = snprintf(NULL, 0, "pex #%d\n", ai->id);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pex #%d\n", ai->id);
    return result;
}

char *player_broadcast(ai_stats_t *ai, char *message)
{
    int alloc = snprintf(NULL, 0, "pbc #%d %s\n", ai->id, message);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pbc #%d %s\n", ai->id, message);
    return result;
}

char *player_death(ai_stats_t *ai)
{
    int alloc = snprintf(NULL, 0, "pdi #%d\n", ai->id);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pdi #%d\n", ai->id);
    return result;
}

char *player_ressources_dropping(ai_stats_t *ai, ressources_index_t i)
{
    int alloc = snprintf(NULL, 0, "pdr #%d %d\n", ai->id, i);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pdr #%d %d\n", ai->id, i);
    return result;
}

char *player_ressources_collecting(ai_stats_t *ai, ressources_index_t i)
{
    int alloc = snprintf(NULL, 0, "pgt #%d %d\n", ai->id, i);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pgt #%d %d\n", ai->id, i);
    return result;
}

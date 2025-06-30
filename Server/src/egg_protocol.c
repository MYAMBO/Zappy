/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** egg_protocol
*/

#include "egg_protocol.h"

char *get_connection_from_egg(slot_t *egg)
{
    int alloc = snprintf(NULL, 0, "ebo #%d\n", egg->global_id);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "ebo #%d\n", egg->global_id);
    return result;
}

char *death_of_an_egg(slot_t *egg)
{
    int alloc = snprintf(NULL, 0, "edi #%d\n", egg->global_id);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "edi #%d\n", egg->global_id);
    return result;
}

char *player_laying_egg(ai_stats_t *ai)
{
    int alloc = snprintf(NULL, 0, "pfk #%d\n", ai->id);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pfk #%d\n", ai->id);
    return result;
}

char *egg_wad_laid(slot_t *slot)
{
    int alloc = snprintf(NULL, 0, "enw #%d #%d %d %d\n",
        slot->global_id, slot->id_user, slot->x, slot->y);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "enw #%d #%d %d %d\n",
        slot->global_id, slot->id_user, slot->x, slot->y);
    return result;
}

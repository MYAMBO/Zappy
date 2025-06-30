/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** egg_protocol
*/

#include "egg_protocol.h"


char *get_connection_from_egg(slot_t *egg)
{
    int alloc = snprintf(NULL, 0, "ebo #%d\n", egg->id_slot);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "ebo #%d\n", egg->id_slot);
    return result;
}

char *death_of_an_egg(slot_t *egg)
{
    int alloc = snprintf(NULL, 0, "edi #%d\n", egg->id_slot);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "edi #%d\n", egg->id_slot);
    return result;
}

char *player_laying_egg(slot_t *slot)
{
    int alloc = snprintf(NULL, 0, "pfk #%d\n", slot->id_user);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "pfk #%d\n", slot->id_user);
    return result;
}

char *egg_wad_laid(slot_t *slot)
{
    int alloc = snprintf(NULL, 0, "enw #%d #%d %d %d\n",
        slot->id_slot, slot->id_user, slot->x, slot->y);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "enw #%d #%d %d %d\n",
        slot->id_slot, slot->id_user, slot->x, slot->y);
    return result;
}


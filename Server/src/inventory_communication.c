/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** inventory_communication
*/

#include "inventory_communication.h"

char *inventory_communication(ai_stats_t *ai)
{
    int alloc = snprintf(NULL, 0,
                    "[food %d, linemate %d, deraumere %d, sibur %d,"
                    " mendiane %d, phiras %d, thystame %d]\n", ai->life,
                    ai->inventory.resources[1], ai->inventory.resources[2],
                    ai->inventory.resources[3],ai->inventory.resources[4],
                    ai->inventory.resources[5], ai->inventory.resources[6]);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1,
        "[food %d, linemate %d, deraumere %d, sibur %d,"
        " mendiane %d, phiras %d, thystame %d]\n", ai->life,
        ai->inventory.resources[1], ai->inventory.resources[2],
        ai->inventory.resources[3],ai->inventory.resources[4],
        ai->inventory.resources[5], ai->inventory.resources[6]);
    return result;
}

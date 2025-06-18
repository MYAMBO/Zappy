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
                    " mendiane %d, phiras %d, thystame %d]", ai->nb_food,
                    ai->nb_linemate, ai->nb_deraumere, ai->nb_sibur,
                    ai->nb_mendiane, ai->nb_phiras, ai->nb_thystame);
    char *result = my_malloc(alloc + 1);

    snprintf(result, alloc + 1,
        "[food %d, linemate %d, deraumere %d, sibur %d,"
        " mendiane %d, phiras %d, thystame %d]", ai->nb_food,
        ai->nb_linemate, ai->nb_deraumere, ai->nb_sibur,
        ai->nb_mendiane, ai->nb_phiras, ai->nb_thystame);
    return result;
}

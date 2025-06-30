/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** time_unit_protocol
*/


#include "time_unit_protocol.h"

char *time_unit_request(server_t *server)
{
    int alloc = snprintf(NULL, 0, "sgt %d\n", server->freq);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "sgt %d\n", server->freq);
    return result;
}

char *time_unit_modification(server_t *server, int new_unit)
{
    int alloc = snprintf(NULL, 0, "sst %d\n", new_unit);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    server->freq = new_unit;
    snprintf(result, alloc + 1, "sst %d\n", new_unit);
    return result;
}

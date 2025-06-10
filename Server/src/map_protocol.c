/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** map_protocol
*/


#include "map_protocol.h"
#include "garbage.h"


char *get_map_size(server_t *server)
{
    int alloc = snprintf(NULL, 0, "msz %d %d\n", server->map_width, server->map_height);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "msz %d %d\n", server->map_width, server->map_height);
    return result;
}

//char *get_tile_items(server_t *server)
//{
//    int alloc = snprintf(NULL, 0, "bct %d %d\n", server->map_width, server->map_height);
//}





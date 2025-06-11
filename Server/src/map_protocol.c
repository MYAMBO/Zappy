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

char *get_tile_content(map_t *map, int x, int y)
{
    int alloc = snprintf(NULL, 0, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        map->tiles[x][y].resources[0],
        map->tiles[x][y].resources[1],
        map->tiles[x][y].resources[2],
        map->tiles[x][y].resources[3],
        map->tiles[x][y].resources[4],
        map->tiles[x][y].resources[5],
        map->tiles[x][y].resources[6]);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
             map->tiles[x][y].resources[0],
             map->tiles[x][y].resources[1],
             map->tiles[x][y].resources[2],
             map->tiles[x][y].resources[3],
             map->tiles[x][y].resources[4],
             map->tiles[x][y].resources[5],
             map->tiles[x][y].resources[6]);
    return result;
}

char *get_map_content(map_t *map)
{
    int total_len = 0;
    char *result = NULL;
    char *tile = NULL;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            total_len += snprintf(NULL, 0, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
                             map->tiles[x][y].resources[0],
                             map->tiles[x][y].resources[1],
                             map->tiles[x][y].resources[2],
                             map->tiles[x][y].resources[3],
                             map->tiles[x][y].resources[4],
                             map->tiles[x][y].resources[5],
                             map->tiles[x][y].resources[6]);
        }
    }
    result = my_malloc(total_len + 1);
    if (!result)
        return NULL;
    result[0] = '\0';
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            tile = get_tile_content(map, x, y);
            if (!tile)
                return NULL;
            strcat(result, tile);
        }
    }
    return result;
}





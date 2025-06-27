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
    int alloc = snprintf(NULL, 0,
        "msz %d %d\n", server->map_width, server->map_height);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1,
        "msz %d %d\n", server->map_width, server->map_height);
    return result;
}

static char *return_tile_ressources(map_t *map, int alloc, int x, int y)
{
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        map->tiles[y][x].resources[0],
        map->tiles[y][x].resources[1],
        map->tiles[y][x].resources[2],
        map->tiles[y][x].resources[3],
        map->tiles[y][x].resources[4],
        map->tiles[y][x].resources[5],
        map->tiles[y][x].resources[6]);
    return result;
}

char *get_tile_content(map_t *map, int x, int y)
{
    int alloc = 0;

    if (x < 0 || y < 0 || x >= map->width || y >= map->height)
        return "sbc\n";
    alloc = snprintf(NULL, 0, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        map->tiles[y][x].resources[0],
        map->tiles[y][x].resources[1],
        map->tiles[y][x].resources[2],
        map->tiles[y][x].resources[3],
        map->tiles[y][x].resources[4],
        map->tiles[y][x].resources[5],
        map->tiles[y][x].resources[6]);
    return return_tile_ressources(map, alloc, x, y);
}

static bool process_map_line(map_t *map, int y, char *result)
{
    char *tile;

    for (int x = 0; x < map->width; x++) {
        tile = get_tile_content(map, x, y);
        if (!tile)
            return false;
        strcat(result, tile);
    }
    return true;
}

static char *concatenate_tile(map_t *map, int total_len)
{
    char *result = NULL;

    result = my_malloc(total_len + 1);
    if (!result)
        return NULL;
    result[0] = '\0';
    for (int y = 0; y < map->height; y++) {
        if (!process_map_line(map, y, result))
            return NULL;
    }
    return result;
}

char *get_map_content(map_t *map)
{
    int total_len = 0;
    char *result = NULL;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            total_len += snprintf(NULL, 0,
                "bct %d %d %d %d %d %d %d %d %d\n", x, y,
                map->tiles[y][x].resources[0],
                map->tiles[y][x].resources[1],
                map->tiles[y][x].resources[2],
                map->tiles[y][x].resources[3],
                map->tiles[y][x].resources[4],
                map->tiles[y][x].resources[5],
                map->tiles[y][x].resources[6]);
        }
    }
    result = concatenate_tile(map, total_len);
    if (result == NULL)
        return NULL;
    return result;
}

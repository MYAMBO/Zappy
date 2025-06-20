/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** look_utils
*/


#include "../include/look_utils.h"

size_t count_visible_tiles(int level)
{
    size_t count = 0;

    for (int d = 0; d <= level; d++)
        count += 2 * d + 1;
    return count;
}

int get_dx(int dir, int d, int p)
{
    int dx[] = {p, d, -p, -d};

    return dx[dir % 4];
}

int get_dy(int dir, int d, int p)
{
    int dy[] = {-d, p, d, -p};

    return dy[dir % 4];
}

void free_tiles(char **tiles, size_t tile_count)
{
    for (size_t i = 0; i < tile_count; i++)
        free(tiles[i]);
    free(tiles);
}

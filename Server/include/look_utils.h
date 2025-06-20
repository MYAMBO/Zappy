/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** look_utils
*/

#ifndef ZAPPY_LOOK_UTILS_H
    #define ZAPPY_LOOK_UTILS_H

    #include <stdio.h>
    #include "string.h"
    #include "server.h"
    #include <stdbool.h>
    #include "garbage.h"

size_t count_visible_tiles(int level);
int get_dx(int dir, int d, int p);
int get_dy(int dir, int d, int p);
void free_tiles(char **tiles, size_t tile_count);

#endif //ZAPPY_LOOK_UTILS_H

/*
** EPITECH PROJECT, 2025
** get_signal_direction.c
** File description:
** get_signal_direction.c
** created and edited by antoiix.
** All rights reserved
*/

#include "player.h"
#include "struct.h"
#include "get_signal_direction.h"

#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

static int inverse_modulo(int n, int m)
{
    if (m < 1)
        return 0;
    if (n > 0)
        return n % m - m;
    if (n < 0)
        return n % m + m;
    return 0;
}

static void get_best_vector(vector_t *vector)
{
    float best_distance = sqrt(vector->x1 * vector->x1 + vector->y1 * vector->y1);
    vector->best_x = vector->x1;
    vector->best_y = vector->y1;

    if (sqrt(vector->x2 * vector->x2 + vector->y2 * vector->y2) < best_distance)
    {
        vector->best_x = vector->x2;
        vector->best_y = vector->y2;
    }
    if (sqrt(vector->x1 * vector->x1 + vector->y2 * vector->y2) < best_distance)
    {
        vector->best_x = vector->x1;
        vector->best_y = vector->y2;
    }
    if (sqrt(vector->x2 * vector->x2 + vector->y1 * vector->y1) < best_distance)
    {
        vector->best_x = vector->x2;
        vector->best_y = vector->y1;
    }
}

static int get_direction(ai_stats_t *receptor, vector_t *vector)
{
    int dir = 0;

    (void)receptor;
    if (vector->best_x == 0 && vector->best_y > 0)
        dir = SOUTH;
    if (vector->best_x == 0 && vector->best_y < 0)
        dir = NORTH;
    if (vector->best_x > 0 && vector->best_y == 0)
        dir = EAST;
    if (vector->best_x < 0 && vector->best_y == 0)
        dir = WEST;
    if (vector->best_x > 0 && vector->best_y > 0 && abs(vector->best_x) > abs(vector->best_y))
        dir = WEST;
    if (vector->best_x > 0 && vector->best_y > 0 && abs(vector->best_x) < abs(vector->best_y))
        dir = SOUTH;
    if (vector->best_x > 0 && vector->best_y < 0 && abs(vector->best_x) > abs(vector->best_y))
        dir = NORTH;
    if (vector->best_x > 0 && vector->best_y < 0 && abs(vector->best_x) < abs(vector->best_y))
        dir = EAST;
    if (vector->best_x < 0 && vector->best_y > 0 && abs(vector->best_x) > abs(vector->best_y))
        dir = WEST;
    if (vector->best_x < 0 && vector->best_y > 0 && abs(vector->best_x) < abs(vector->best_y))
        dir = SOUTH;
    if (vector->best_x < 0 && vector->best_y < 0 && abs(vector->best_x) > abs(vector->best_y))
        dir = WEST;
    if (vector->best_x < 0 && vector->best_y < 0 && abs(vector->best_x) < abs(vector->best_y))
        dir = NORTH;
    if (vector->best_x > 0 && vector->best_y > 0 && abs(vector->best_x) == abs(vector->best_y))
        dir = SOUTH_EAST;
    if (vector->best_x > 0 && vector->best_y < 0 && abs(vector->best_x) == abs(vector->best_y))
        dir = NORTH_EAST;
    if (vector->best_x < 0 && vector->best_y > 0 && abs(vector->best_x) == abs(vector->best_y))
        dir = SOUTH_EAST;
    if (vector->best_x < 0 && vector->best_y < 0 && abs(vector->best_x) == abs(vector->best_y))
        dir = NORTH_WEST;
    dir -= receptor->direction;
    if (dir < 0)
        dir += 8;
    return dir + 1;
}

int get_signal_direction(ai_stats_t *source, ai_stats_t *receptor, server_t *server)
{
    int x = source->x - receptor->x;
    int y = source->y - receptor->y;
    vector_t vector = {0};

    // printf("%d %d // %d %d %d %d\n", x, y, source->x, source->y, receptor->x, receptor->y);
    if (x == 0 && y == 0)
        return 0;
    vector.x1 = x;
    vector.y1 = y;
    vector.x2 = inverse_modulo(x, server->map_width);
    vector.y2 = inverse_modulo(y, server->map_height);
    get_best_vector(&vector);
    // printf("best : %d %d\n", vector.best_x, vector.best_y);
    return get_direction(receptor, &vector);
}

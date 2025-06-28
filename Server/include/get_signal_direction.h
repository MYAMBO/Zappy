/*
** EPITECH PROJECT, 2025
** get_signal_direction.h
** File description:
** get_signal_direction.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef GET_SIGNAL_DIRECTION_H
    #define GET_SIGNAL_DIRECTION_H

typedef struct vector_s {
    int x1;
    int y1;
    int y2;
    int x2;
    int best_x;
    int best_y;
} vector_t;

int get_signal_direction(ai_stats_t *source, ai_stats_t *receptor,
    server_t *server);

#endif //GET_SIGNAL_DIRECTION_H

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** look_around_communication
*/


#ifndef ZAPPY_LOOK_AROUND_COMMUNICATION_H
    #define ZAPPY_LOOK_AROUND_COMMUNICATION_H

    #include <stdio.h>
    #include "string.h"
    #include "server.h"
    #include <stdbool.h>
    #include "garbage.h"
    #include "look_utils.h"

typedef struct tile_context_s {
    map_t *map;
    poll_handling_t *players;
    int x;
    int y;
} tile_context_t;

typedef struct tile_info_s {
    int total_len;
    int total_words;
} tile_info_t;

typedef struct look_context_s {
    ai_stats_t *ai;
    poll_handling_t *players;
    map_t *map;
} look_context_t;

typedef struct fill_tile_info_s {
    char **tiles;
    size_t *tile_count;
    size_t *total_len;
} fill_tile_info_t;


char *player_looks_around(ai_stats_t *ai,
    poll_handling_t *players, map_t *map);

#endif //ZAPPY_LOOK_AROUND_COMMUNICATION_H

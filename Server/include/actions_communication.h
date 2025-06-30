/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** actions_communication
*/


#ifndef ZAPPY_ACTIONS_COMMUNICATION_H
    #define ZAPPY_ACTIONS_COMMUNICATION_H


    #include <stdio.h>
    #include "string.h"
    #include "server.h"
    #include "garbage.h"
    #include <stdbool.h>

char *player_plays_broadcast(ai_stats_t *ai, char *text, server_t *server);
char *get_slot_remaining(ai_stats_t *ai, server_t *server);
char *can_player_takes_items(ai_stats_t *ai, map_t *map,
    char *item, server_t *server);
char *can_player_drops_items(ai_stats_t *ai, map_t *map,
    char *item, server_t *server);


#endif //ZAPPY_ACTIONS_COMMUNICATION_H

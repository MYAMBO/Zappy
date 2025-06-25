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

char *death_of_player(ai_stats_t *ai);
char *player_plays_broadcast(ai_stats_t *ai, char *text);
char *can_player_takes_items(ai_stats_t *ai, map_t *map, char *item);


#endif //ZAPPY_ACTIONS_COMMUNICATION_H

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** eject_communication
*/


#ifndef ZAPPY_EJECT_COMMUNICATION_H
    #define ZAPPY_EJECT_COMMUNICATION_H

    #include <stdio.h>
    #include "string.h"
    #include "server.h"
    #include "garbage.h"
    #include <stdbool.h>

char *eject_player(ai_stats_t *ai, poll_handling_t *players, map_t *map, server_t *server);
#endif //ZAPPY_EJECT_COMMUNICATION_H

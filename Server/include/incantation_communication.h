/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** incantation_communication
*/


#ifndef ZAPPY_INCANTATION_COMMUNICATION_H
    #define ZAPPY_INCANTATION_COMMUNICATION_H

    #include <stdio.h>
    #include "string.h"
    #include "server.h"
    #include "garbage.h"
    #include <stdbool.h>

char *start_incantation(ai_stats_t *lead,
    server_t *server, map_t *map);
char *end_incantation(server_t *server, map_t *map);

#endif //ZAPPY_INCANTATION_COMMUNICATION_H

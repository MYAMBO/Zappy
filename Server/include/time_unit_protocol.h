/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** time_unit_protocol
*/


#ifndef ZAPPY_TIME_UNIT_PROTOCOL_H
    #define ZAPPY_TIME_UNIT_PROTOCOL_H

    #include "stdio.h"
    #include "string.h"
    #include "server.h"
    #include "garbage.h"
    #include "player.h"

char *time_unit_request(server_t *server);
char *time_unit_modification(server_t *server, int new_unit);

#endif //ZAPPY_TIME_UNIT_PROTOCOL_H

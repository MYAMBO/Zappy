/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** movements_communication
*/

#ifndef ZAPPY_MOVEMENTS_COMMUNICATION_H
    #define ZAPPY_MOVEMENTS_COMMUNICATION_H

    #include "string.h"
    #include "server.h"
    #include <stdbool.h>


char *player_turns_right(ai_stats_t *ai);
char *handle_forward_action(ai_stats_t *ai, server_t *server);

#endif //ZAPPY_MOVEMENTS_COMMUNICATION_H

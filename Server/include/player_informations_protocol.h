/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** player_informations_protocol
*/


#ifndef ZAPPY_PLAYER_INFORMATIONS_PROTOCOL_H
    #define ZAPPY_PLAYER_INFORMATIONS_PROTOCOL_H

    #include "stdio.h"
    #include "string.h"
    #include "server.h"
    #include "garbage.h"
    #include "player.h"

char *get_teams_name(server_t *server);
char *get_player_level(ai_stats_t ai);
char *get_player_position(ai_stats_t ai);
char *get_player_inventory(ai_stats_t *ai, int x, int y);
char *end_of_game(ai_stats_t *ai);

#endif //ZAPPY_PLAYER_INFORMATIONS_PROTOCOL_H

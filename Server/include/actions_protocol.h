/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** actions_protocol
*/


#ifndef ZAPPY_ACTIONS_PROTOCOL_H
    #define ZAPPY_ACTIONS_PROTOCOL_H

    #include "stdio.h"
    #include "server.h"
    #include "garbage.h"

char *player_death(ai_stats_t *ai);
char *player_expulsion(ai_stats_t *ai);
char *player_broadcast(ai_stats_t *ai, char *message);
char *player_ressources_collecting(ai_stats_t *ai, ressources_index_t i);
char *player_ressources_dropping(ai_stats_t *ai, ressources_index_t i);



#endif //ZAPPY_ACTIONS_PROTOCOL_H

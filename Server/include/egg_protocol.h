/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** egg_protocol
*/

#ifndef ZAPPY_EGG_PROTOCOL_H
    #define ZAPPY_EGG_PROTOCOL_H

    #include "stdio.h"
    #include "string.h"
    #include "server.h"
    #include "garbage.h"
    #include "player.h"

char *get_connection_from_egg(slot_t *egg);
char *death_of_an_egg(slot_t *egg);
char *player_laying_egg(ai_stats_t *ai);
char *egg_wad_laid(slot_t *slot);

#endif //ZAPPY_EGG_PROTOCOL_H

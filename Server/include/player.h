/*
** EPITECH PROJECT, 2025
** player.h
** File description:
** player.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef PLAYER_H
    #define PLAYER_H

    #include <stdbool.h>

typedef struct ressources_s {
    int resources[7]; // all possible ressources
} ressources_t;

typedef struct ai_stats_s {
    bool connected;
    int fd;
    char *tmp_command;
    int id;
    int life;
    int x;
    int y;
    int direction; //N, S, E, W
    int level;
    char *team_name;
    int nb_food;
    int nb_linemate;
    int nb_deraumere;
    int nb_sibur;
    int nb_mendiane;
    int nb_phiras;
    int nb_thystame;
    bool in_incantation;
    ressources_t inventory;
} ai_stats_t;

#endif //PLAYER_H

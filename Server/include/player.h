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

typedef struct command_exec_s {
    char **args;
    int tick_launch;
    int time_to_exec;
    struct command_exec_s *next;
} command_exec_t;

typedef struct ai_stats_s {
    int nb_command_exec;
    command_exec_t *command_exec_list;
    bool connected;
    int fd;
    char *tmp_command;
    int id;
    int life;
    int x;
    int y;
    int direction; //N, S, E, W
    int level;
    int last_life;
    char *team_name;
    int in_incantation;
    bool is_alive;
    ressources_t inventory;
} ai_stats_t;

#endif //PLAYER_H

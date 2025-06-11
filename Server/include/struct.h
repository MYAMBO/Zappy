/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** struct.h
** created and edited by antoiix.
** All rights reserved
*/



#ifndef STRUCT_H
    #define STRUCT_H

    #include "poll_handling.h"
    #include <stdbool.h>



typedef struct server_s {
    long port;
    int server_fd;
    poll_handling_t *poll_list;
    int poll_count;




    int map_width;
    int map_height;
    char **team_names;
    int team_count;
    int nb_clients;
    int freq;
    double food_density;
    double linemate_density;
    double deraumere_density;
    double sibur_density;
    double mendiane_density;
    double phiras_density;
    double thystame_density;

} server_t;

typedef struct entry_s {
    char *command;
    void (*function)(poll_handling_t *poll, server_t *server);
} entry_t;

typedef struct ressources_s {
    int resources[7]; // all possible ressources
} ressources_t;

typedef struct ai_stats_s {
    int id;
    int life;
    int x;
    int y;
    int direction; //N, S, E, W
    int level;
    char *team_name;
//    int nb_food;
//    int nb_linemate;
//    int nb_deraumere;
//    int nb_sibur;
//    int nb_mendiane;
//    int nb_phiras;
//    int nb_thystame;
    bool in_incantation;
    ressources_t inventory;
} ai_stats_t;

/*
 *
 *  include the following map_t in the server struct after some
 *  amelioration
 *
*/

typedef struct map_s {
    int width;
    int height;
    ressources_t **tiles;
} map_t;

#endif //STRUCT_H

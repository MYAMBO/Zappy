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
    #include <time.h>
    #include "slot_struct.h"

typedef enum ressources_index_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} ressources_index_t;

typedef enum direction_s {
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST,
} direction_t;

typedef struct map_s {
    int width;
    int height;
    ressources_t **tiles;
} map_t;

typedef struct incantation_list_s
{
    int incantation_nb;
    int tick_end;
    int x;
    int y;
    int level_base;
    struct incantation_list_s *next;
} incantation_list_t;

typedef struct server_s {
    clock_t base_time;
    incantation_list_t *incantation_list;
    int tick;
    long port;
    int server_fd;
    poll_handling_t *poll_list;
    int poll_count;
    int map_width;
    int map_height;
    map_t *map;
    slot_table_t **team_names;
    int team_count;
    int client_per_slot;
    int freq;
    double food_density;
    double linemate_density;
    double deraumere_density;
    double sibur_density;
    double mendiane_density;
    double phiras_density;
    double thystame_density;
    int food_value;
    int linemate_value;
    int deraumere_value;
    int sibur_value;
    int mendiane_value;
    int phiras_value;
    int thystame_value;
    int current_res[7];
    int regenerate_time;
    bool finished;
} server_t;

typedef struct entry_ai_s {
    char *command;
    int (*function)(server_t *server, poll_handling_t *node, char **args);
    int time;
} entry_ai_t;

typedef struct entry_gui_s {
    char *command;
    int (*function)(server_t *server, poll_handling_t *node, char **args);
} entry_gui_t;

#endif //STRUCT_H

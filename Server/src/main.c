/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"
#include "server.h"
#include "struct.h"
#include "logger.h"
#include "options_parser.h"

#include "map_protocol.h"
#include "technical_protocol.h"
#include "player_informations_protocol.h"
#include "actions_protocol.h"
#include <time.h>
#include <stdbool.h>
#include "movements_communication.h"

map_t *init_test_map(int width, int height)
{
    map_t *map = my_malloc(sizeof(map_t));

    srand(time(NULL));
    map->width = width;
    map->height = height;
    map->tiles = my_malloc(sizeof(ressources_t *) * height);
    for (int y = 0; y < height; y++) {
        map->tiles[y] = my_malloc(sizeof(ressources_t) * width);
        for (int x = 0; x < width; x++) {
            for (int i = 0; i < 7; i++)
                map->tiles[y][x].resources[i] = rand() % 100;
        }
    }
    printf("%s", get_map_content(map));
    return map;
}

ai_stats_t *create_test_ai(int id, const char *team_name, server_t *server)
{
    ai_stats_t *ai = malloc(sizeof(ai_stats_t));

    if (!ai)
        return NULL;
    ai->connected = true;
    ai->fd = id + 3;
    ai->tmp_command = NULL;
    ai->id = id;
    ai->life = 126;
    ai->x = server->map_height - 1;
    ai->y = server->map_width;
    ai->direction = NORTH;
    ai->level = 1;
    ai->team_name = strdup(team_name);
    ai->nb_food = 3;
    ai->nb_linemate = 1;
    ai->nb_deraumere = 0;
    ai->nb_sibur = 0;
    ai->nb_mendiane = 0;
    ai->nb_phiras = 0;
    ai->nb_thystame = 0;
    ai->in_incantation = false;
    for (int i = 0; i < 7; i++)
        ai->inventory.resources[i] = rand() % 3;

    return ai;
}

int parse_arguments(int ac, char **av, server_t *server)
{
    if (ac < 2)
        return FAILURE;
    if (parse_port(av, server) == FAILURE)
        return FAILURE;
    if (parse_map_size(av, server) == FAILURE)
        return FAILURE;
    if (parse_clients_nb(av, server) == FAILURE)
        return FAILURE;
    if (parse_team_names(av, server) == FAILURE)
        return FAILURE;
    if (parse_freq(av, server) == FAILURE)
        return FAILURE;

    //test part

    ai_stats_t *ai = create_test_ai(0, "noot", server);
    printf("%d\n", ai->direction);
    player_turns_right(ai);
    printf("%d\n", ai->direction);


    return SUCCESS;
}

int main(int ac, char **av)
{
    server_t server;

    init_density(&server);
    logger_clear_log_file();
    logger_info("Server starting...", FILE_OUTPUT, true);
    if (parse_arguments(ac, av, &server) == FAILURE ||
        start_server(&server) == FAILURE) {
        free_garbage();
        return FAILURE;
    }
    free_garbage();
    return SUCCESS;
}

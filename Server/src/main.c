/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include <signal.h>
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
#include "inventory_communication.h"
#include "actions_communication.h"
#include "look_around_communication.h"
#include "eject_communication.h"
#include "incantation_communication.h"
#include "generate_ressources.h"

map_t *init_map(int width, int height)
{
    map_t *map = my_malloc(sizeof(map_t));

    if (!map)
        return NULL;
    srand(time(NULL));
    map->width = width;
    map->height = height;
    map->tiles = my_malloc(sizeof(ressources_t *) * height);
    if (!map->tiles)
        return NULL;
    for (int y = 0; y < height; y++) {
        map->tiles[y] = my_malloc(sizeof(ressources_t) * width);
        if (!map->tiles[y])
            return NULL;
        for (int x = 0; x < width; x++) {
            for (int i = 0; i < 7; i++)
                map->tiles[y][x].resources[i] = 0;
        }
    }
    return map;
}

int parse_arguments(int ac, char **av, server_t *server)
{
    if (ac < 2)
        return FAILURE;
    if (parse_port(av, server) == FAILURE)
        return FAILURE;
    if (parse_map_size(av, server) == FAILURE)
        return FAILURE;
    server->map = init_map(server->map_width, server->map_height);
    if (server->map == NULL)
        return FAILURE;
    if (parse_clients_nb(av, server) == FAILURE)
        return FAILURE;
    if (parse_team_names(av, server) == FAILURE)
        return FAILURE;
    if (parse_freq(av, server) == FAILURE)
        return FAILURE;
    init_density(server);
    generate_all_ressources(server);
    return SUCCESS;
}

int *is_running(void)
{
    static int is_running = 1;

    return &is_running;
}

void stop_server(int tmp)
{
    int *val = is_running();

    (void)tmp;
    *val = 0;
}

int main(int ac, char **av)
{
    server_t server;

    signal(SIGINT, stop_server);
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

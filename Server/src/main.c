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
#include <time.h>

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

    //printf("%s", get_tile_content(map, 2, 3));
    printf("%s", get_map_content(map));  // get_map_content calls get_tile_content


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
    if (parse_clients_nb(av, server) == FAILURE)
        return FAILURE;
    if (parse_team_names(av, server) == FAILURE)
        return FAILURE;
    if (parse_freq(av, server) == FAILURE)
        return FAILURE;

    init_test_map(server->map_width, server->map_height);

    printf("%s", get_map_size(server));
    printf("%s", get_teams_name(server));
    printf("%s", get_unknown_command());
    printf("%s", get_server_message("test"));

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

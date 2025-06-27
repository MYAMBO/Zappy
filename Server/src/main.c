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
#include "player_connection_protocol.h"

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

//create one AI to test

//ai_stats_t *create_test_ai(int id, const char *team_name, server_t *server)
//{
//    ai_stats_t *ai = malloc(sizeof(ai_stats_t));
//
//    if (!ai)
//        return NULL;
//    ai->connected = true;
//    ai->fd = id + 3;
//    ai->tmp_command = NULL;
//    ai->id = id;
//    ai->life = 126;
//    ai->x = server->map_width - 1;
//    ai->y = server->map_height - 1;
//    ai->direction = SOUTH;
//    ai->level = 1;
//    ai->team_name = strdup(team_name);
//    ai->nb_food = 3;
//    ai->nb_linemate = 1;
//    ai->nb_deraumere = 6;
//    ai->nb_sibur = 5;
//    ai->nb_mendiane = 8;
//    ai->nb_phiras = 2;
//    ai->nb_thystame = 3;
//    ai->in_incantation = false;
//    for (int i = 0; i < 7; i++)
//        ai->inventory.resources[i] = rand() % 3;
//
//    return ai;
//}


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

static void show_usage(void)
{
    printf("\nZAPPY_SERVER HELP:\n\nMANDATORY OPTIONS:\n\n"
        "  -p NUMBER: port used by the server\n"
        "  -x NUMBER: width of the map\n"
        "  -y NUMBER: height of the map\n"
        "  -c NUMBER: total of slots available per team\n"
        "  -n STRING STRING ...: all team names available"
        "\n\nNON MANDATORY OPTIONS:\n\n"
        "  -f NUMBER: freq used (100 by default)"
        "\n\nUSAGE:\n"
        "  $ ./zappy_server -p 1234 -x 2 -y 5 -c 10 -n team1 team2 -f 60\n\n"

        );
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
        show_usage();
        return FAILURE;
    }
    free_garbage();
    return SUCCESS;
}

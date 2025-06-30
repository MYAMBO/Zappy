/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** generate_ressources
*/


#include "generate_ressources.h"

static void generate_ressource(server_t *server, map_t *map, int max, int i)
{
    int width = map->width;
    int height = map->height;
    int x = 0;
    int y = 0;
    int generation = max - server->current_res[i];

    while (generation > 0) {
        printf("Generations\n");
        x = rand() % width;
        y = rand() % height;
        map->tiles[y][x].resources[i]++;
        server->current_res[i]++;
        generation--;
    }
}

void generate_all_ressources(server_t *server)
{
    generate_ressource(server, server->map, server->food_value, 0);
    generate_ressource(server, server->map, server->linemate_value, 1);
    generate_ressource(server, server->map, server->deraumere_value, 2);
    generate_ressource(server, server->map, server->sibur_value, 3);
    generate_ressource(server, server->map, server->mendiane_value, 4);
    generate_ressource(server, server->map, server->phiras_value, 5);
    generate_ressource(server, server->map, server->thystame_value, 6);
}

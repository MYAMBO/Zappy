/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** init_density
*/

#include "server.h"

static void around_up_value(server_t *server)
{
    if (server->food_value < 1)
        server->food_value = 1;
    if (server->linemate_value < 1)
        server->linemate_value = 1;
    if (server->deraumere_value < 1)
        server->deraumere_value = 1;
    if (server->sibur_value < 1)
        server->sibur_value = 1;
    if (server->mendiane_value < 1)
        server->mendiane_value = 1;
    if (server->phiras_value < 1)
        server->phiras_value = 1;
    if (server->thystame_value < 1)
        server->thystame_value = 1;
}

void init_density(server_t *server)
{
    int x = server->map_width;
    int y = server->map_height;

    server->food_density = 0.5;
    server->linemate_density = 0.3;
    server->deraumere_density = 0.15;
    server->sibur_density = 0.1;
    server->mendiane_density = 0.1;
    server->phiras_density = 0.08;
    server->thystame_density = 0.05;
    server->food_value = x * y * server->food_density;
    server->linemate_value = x * y * server->linemate_density;
    server->deraumere_value = x * y * server->deraumere_density;
    server->sibur_value = x * y * server->sibur_density;
    server->mendiane_value = x * y * server->mendiane_density;
    server->phiras_value = x * y * server->phiras_density;
    server->thystame_value = x * y * server->thystame_density;
    around_up_value(server);
}

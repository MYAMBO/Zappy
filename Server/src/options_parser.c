/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** options_parser
*/


#include "options_parser.h"

#include "slot_handler.h"

int parse_port(char **av, server_t *server)
{
    int found = 0;
    int nb = 0;
    long port;
    char *end_ptr;

    for (int i = 0; av[i] != NULL; i++){
        if (strcmp(av[i], "-p") == 0){
            found++;
            nb = i;
        }
    }
    if (found != 1 || av[nb + 1] == NULL)
        return FAILURE;
    port = strtol(av[nb + 1], &end_ptr, 0);
    if (*end_ptr != '\0')
        return FAILURE;
    if (init_server(server, port) == FAILURE)
        return FAILURE;
    server->port = port;
    return SUCCESS;
}

static int parse_width(char **av, server_t *server)
{
    int found_x = 0;
    int nb_x = 0;
    int width = 0;

    for (int i = 0; av[i] != NULL; i++){
        if (strcmp(av[i], "-x") == 0){
            found_x++;
            nb_x = i;
        }
    }
    if (found_x != 1 || av[nb_x + 1] == NULL)
        return FAILURE;
    width = atoi(av[nb_x + 1]);
    if (width < 10 || width > 42)
        return FAILURE;
    server->map_width = width;
    return SUCCESS;
}

static int parse_height(char **av, server_t *server)
{
    int found_y = 0;
    int nb_y = 0;
    int height = 0;

    for (int i = 0; av[i] != NULL; i++){
        if (strcmp(av[i], "-y") == 0){
            found_y++;
            nb_y = i;
        }
    }
    if (found_y != 1 || av[nb_y + 1] == NULL)
        return FAILURE;
    height = atoi(av[nb_y + 1]);
    if (height < 10 || height > 42)
        return FAILURE;
    server->map_height = height;
    return SUCCESS;
}

int parse_map_size(char **av, server_t *server)
{
    if (parse_width(av, server) == FAILURE)
        return FAILURE;
    if (parse_height(av, server) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int parse_clients_nb(char **av, server_t *server)
{
    int found = 0;
    int nb = 0;
    int nb_clients = 0;

    for (int i = 0; av[i] != NULL; i++){
        if (strcmp(av[i], "-c") == 0){
            found++;
            nb = i;
        }
    }
    if (found != 1 || av[nb + 1] == NULL)
        return FAILURE;
    nb_clients = atoi(av[nb + 1]);
    if (nb_clients <= 0)
        return FAILURE;
    server->client_per_slot = nb_clients;
    return SUCCESS;
}

static int show_current_team_name(server_t *server,
    char **av, int count, int back_nb)
{
    if (count == 0)
        return FAILURE;
    server->team_names = my_malloc(sizeof(slot_table_t *) * (count + 2));
    if (!server->team_names)
        return FAILURE;
    for (int j = 1; j < count + 1; j++) {
        server->team_names[j] = create_slot_table(server->client_per_slot,
            av[back_nb + j - 1], server);
        if (!server->team_names[j])
            return FAILURE;
    }
    server->team_names[0] = create_slot_table(1, "GRAPHIC", server);
    if (!server->team_names[0])
        return FAILURE;
    server->team_names[count + 1] = NULL;
    server->team_count = count;
    return SUCCESS;
}

static int search_team_name(char **av, int nb, server_t *server)
{
    int back_nb = nb;
    int count = 0;

    for (; av[nb] != NULL; nb++){
        if (strcmp(av[nb], "-p") == 0 ||
            strcmp(av[nb], "-x") == 0 ||
            strcmp(av[nb], "-y") == 0 ||
            strcmp(av[nb], "-n") == 0 ||
            strcmp(av[nb], "-c") == 0 ||
            strcmp(av[nb], "-f") == 0)
            break;
        count++;
    }
    if (show_current_team_name(server, av, count, back_nb) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int parse_team_names(char **av, server_t *server)
{
    int found = 0;
    int nb = 0;

    for (int i = 0; av[i] != NULL; i++){
        if (strcmp(av[i], "-n") == 0){
            found++;
            nb = i;
        }
    }
    if (found != 1 || av[nb + 1] == NULL)
        return FAILURE;
    if (search_team_name(av, nb + 1, server) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

static int attribute_freq(int nb, int found, char **av, server_t *server)
{
    int freq = 0;

    if (found != 1 || av[nb + 1] == NULL)
        return FAILURE;
    freq = atoi(av[nb + 1]);
    if (freq <= 0)
        return FAILURE;
    server->freq = freq;
    return SUCCESS;
}

int parse_freq(char **av, server_t *server)
{
    int found = 0;
    int nb = 0;

    for (int i = 0; av[i] != NULL; i++){
        if (strcmp(av[i], "-f") == 0){
            found++;
            nb = i;
        }
    }
    if (found == 0) {
        server->freq = 100;
        return SUCCESS;
    }
    if (attribute_freq(nb, found, av, server) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

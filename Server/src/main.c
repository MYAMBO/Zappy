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

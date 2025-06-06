/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "garbage.h"
#include "server.h"
#include "struct.h"
#include "logger.h"

int parse_arguments(int ac, char **av, server_t *server)
{
    long port;
    char *end_ptr;

    if (ac != 2)
        return FAILURE;
    port = strtol(av[1], &end_ptr, 0);
    if (*end_ptr != '\0')
        return FAILURE;
    if (init_server(server, port) == FAILURE)
        return FAILURE;
    server->port = port;
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

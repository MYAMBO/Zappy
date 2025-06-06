/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** options_parser
*/


#ifndef ZAPPY_OPTIONS_PARSER_H
    #define ZAPPY_OPTIONS_PARSER_H

#include "struct.h"
#include "server.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "garbage.h"


int parse_port(char **av, server_t *server);
int parse_map_size(char **av, server_t *server);
int parse_clients_nb(char **av, server_t *server);
int parse_team_names(char **av, server_t *server);
int parse_freq(char **av, server_t *server);

#endif //ZAPPY_OPTIONS_PARSER_H

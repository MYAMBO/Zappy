/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** incantation_protocol
*/


#ifndef ZAPPY_INCANTATION_PROTOCOL_H
    #define ZAPPY_INCANTATION_PROTOCOL_H

    #include <stdio.h>
    #include "string.h"
    #include "server.h"
    #include "garbage.h"
    #include <stdbool.h>

char *start_incantation_protocol(ai_stats_t *lead, ai_stats_t *rest[]);
char *end_incantation_protocol(incantation_list_t *incantation, bool status);

#endif //ZAPPY_INCANTATION_PROTOCOL_H

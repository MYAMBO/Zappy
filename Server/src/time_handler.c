/*
** EPITECH PROJECT, 2025
** time_handler.c
** File description:
** time_handler.c
** created and edited by antoiix.
** All rights reserved
*/

#include "time_handler.h"
#include <stdio.h>

bool increase_tick(server_t *server)
{
    if (((float)clock() - (float)server->base_time) / (float)CLOCKS_PER_SEC >=
        (float)1 / ((float)1000 * (float)server->freq)){
        server->base_time = clock();
        server->tick++;
        return true;
    }
    return false;
}

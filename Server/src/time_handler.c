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
    float target_interval = (float)1 / ((float)1000 * (float)server->freq);
    float current_time = (float)clock() / (float)CLOCKS_PER_SEC;
    float base_time = (float)server->base_time / (float)CLOCKS_PER_SEC;
    
    if (current_time >= base_time + target_interval) {
        server->base_time = server->base_time + (clock_t)(target_interval * CLOCKS_PER_SEC);
        server->tick++;
        return true;
    }
    return false;
}
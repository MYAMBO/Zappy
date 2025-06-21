/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** eject_communication
*/


#include "eject_communication.h"

static void eject_in_look_direction(ai_stats_t *ai,
    ai_stats_t *target, map_t *map)
{
    if (ai->direction == NORTH){
        if (ai->y == 0){
            target->y = map->height - 1;
            return;
        }
        target->y -= 1;

    }
    if (ai->direction == EAST){
        if (ai->x == map->width - 1){
            target->x = 0;
            return;
        }
        target->x += 1;
    }
    if (ai->direction == SOUTH){
        if (ai->y == map->height - 1){
            target->y = 0;
            return;
        }
        target->y += 1;
    }
    if (ai->direction == WEST){
        if (ai->x == 0){
            target->x = map->width - 1;
            return;
        }
        target->x -= 1;
    }
}


char *eject_player(ai_stats_t *ai, poll_handling_t *players, map_t *map)
{
    bool ejected = false;
    ai_stats_t *current = NULL;


    for (poll_handling_t *poll = players; poll != NULL; poll = poll->next) {
        current = poll->player;
        if (current == ai || !current)
            continue;
        if (current->x == ai->x && current->y == ai->y) {
            eject_in_look_direction(ai, current, map);
            ejected = true;
        }
    }
    if (ejected)
        return "ok";
    return "ko";
}
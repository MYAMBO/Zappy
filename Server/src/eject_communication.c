/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** eject_communication
*/


#include "eject_communication.h"

#include <unistd.h>

#include "get_signal_direction.h"
#include "look_around_communication.h"

static void eject_east_west(ai_stats_t *ai, ai_stats_t *target, map_t *map, server_t *server)
{
    if (ai->direction == EAST){
        if (ai->x == map->width - 1){
            target->x = 0;
        }
        else
            target->x += 1;
        int a = snprintf(NULL, 0, "eject %d\n", get_signal_direction(ai, target, server));
        char *str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n", get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
    if (ai->direction == WEST){
        if (ai->x == 0){
            target->x = map->width - 1;
        }
        else
            target->x -= 1;
        int a = snprintf(NULL, 0, "eject %d\n", get_signal_direction(ai, target, server));
        char *str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n", get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
}

static void eject_north_south(ai_stats_t *ai, ai_stats_t *target, map_t *map, server_t *server)
{
    if (ai->direction == NORTH){
        if (ai->y == 0){
            target->y = map->height - 1;
        }
        else
            target->y -= 1;
        int a = snprintf(NULL, 0, "eject %d\n", get_signal_direction(ai, target, server));
        char *str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n", get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
    if (ai->direction == SOUTH){
        if (ai->y == map->height - 1){
            target->y = 0;
        }
        else
            target->y += 1;
        int a = snprintf(NULL, 0, "eject %d\n", get_signal_direction(ai, target, server));
        char *str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n", get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
}

static void eject_in_look_direction(ai_stats_t *ai,
    ai_stats_t *target, map_t *map, server_t *server)
{
    eject_north_south(ai, target, map, server);
    eject_east_west(ai, target, map, server);
}

char *eject_player(ai_stats_t *ai, poll_handling_t *players, map_t *map, server_t *server)
{
    bool ejected = false;
    ai_stats_t *current = NULL;

    for (poll_handling_t *poll = players; poll != NULL; poll = poll->next) {
        current = poll->player;
        if (current == ai || !current || strcmp(current->team_name, "GRAPHIC") == 0)
            continue;
        if (current->x == ai->x && current->y == ai->y) {
            eject_in_look_direction(ai, current, map, server);
            ejected = true;
        }
    }
    if (ejected)
        return "ok\n";
    return "ko\n";
}

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** eject_communication
*/

#include "eject_communication.h"
#include <unistd.h>

#include "egg_protocol.h"
#include "get_signal_direction.h"
#include "look_around_communication.h"
#include "slot_handler.h"
#include "utils.h"

static void eject_east(ai_stats_t *ai, ai_stats_t *target,
                       map_t *map, server_t *server)
{
    int a;
    char *str;

    if (ai->direction == EAST) {
        if (ai->x == map->width - 1) {
            target->x = 0;
        } else
            target->x += 1;
        a = snprintf(NULL, 0, "eject %d\n",
            get_signal_direction(ai, target, server));
        str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n",
            get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
}

static void eject_west(ai_stats_t *ai, ai_stats_t *target,
    map_t *map, server_t *server)
{
    int a;
    char *str;

    if (ai->direction == WEST) {
        if (ai->x == 0) {
            target->x = map->width - 1;
        } else
            target->x -= 1;
        a = snprintf(NULL, 0, "eject %d\n",
            get_signal_direction(ai, target, server));
        str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n",
            get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
}

static void eject_north(ai_stats_t *ai, ai_stats_t *target,
    map_t *map, server_t *server)
{
    int a;
    char *str;

    if (ai->direction == NORTH) {
        if (ai->y == 0) {
            target->y = map->height - 1;
        } else
            target->y -= 1;
        a = snprintf(NULL, 0, "eject %d\n",
            get_signal_direction(ai, target, server));
        str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n",
            get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
}

static void eject_south(ai_stats_t *ai, ai_stats_t *target,
    map_t *map, server_t *server)
{
    int a;
    char *str;

    if (ai->direction == SOUTH) {
        if (ai->y == map->height - 1) {
            target->y = 0;
        } else
            target->y += 1;
        a = snprintf(NULL, 0, "eject %d\n",
            get_signal_direction(ai, target, server));
        str = my_malloc(a + 1);
        snprintf(str, a + 1, "eject %d\n",
            get_signal_direction(ai, target, server));
        write(target->fd, str, strlen(str));
    }
}

static void eject_in_look_direction(ai_stats_t *ai,
    ai_stats_t *target, map_t *map, server_t *server)
{
    eject_north(ai, target, map, server);
    eject_south(ai, target, map, server);
    eject_east(ai, target, map, server);
    eject_west(ai, target, map, server);
}

char *eject_player(ai_stats_t *ai, poll_handling_t *players,
    map_t *map, server_t *server)
{
    bool ejected = false;
    ai_stats_t *current = NULL;
    slot_t *next = NULL;
    char *str;

    for (int i = 0; server->team_names[i] != NULL; i++) {
        for (slot_t *slot = server->team_names[i]->slots; slot != NULL; slot = next) {
            next = slot->next;
            if (slot->id_user == -1 && slot->x == ai->x && slot->y == ai->y)
            {
                remove_slot(&server->team_names[i]->slots, slot->id_slot);
                str = death_of_an_egg(slot);
                if (!str)
                    return NULL;
                send_message_graphic(server, str);
                my_free(str);
            }
        }
    }
    for (poll_handling_t *poll = players; poll != NULL; poll = poll->next) {
        current = poll->player;
        if (current == ai || !current ||
            strcmp(current->team_name, "GRAPHIC") == 0)
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

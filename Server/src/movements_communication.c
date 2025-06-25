/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** movements_communication
*/


#include "movements_communication.h"

#include <stdio.h>

static bool verif_out_map_player(server_t *serv, ai_stats_t *ai, int x, int y)
{
    if (ai->x + x >= serv->map_height) {
        ai->x = 0;
        return true;
    }
    if (ai->y + y >= serv->map_width) {
        ai->y = 0;
        return true;
    }
    if (ai->x + x < 0) {
        ai->x = serv->map_height - 1;
        return true;
    }
    if (ai->y + y < 0) {
        ai->y = serv->map_width - 1;
        return true;
    }
    return false;
}

char *handle_forward_action(ai_stats_t *ai, server_t *server)
{
    if (ai->direction == NORTH) {
        if (verif_out_map_player(server, ai, 0, -1) == false)
            ai->y -= 1;
    }
    if (ai->direction == SOUTH){
        if (verif_out_map_player(server, ai, 0, 1) == false)
            ai->y += 1;
    }
    if (ai->direction == EAST){
        if (verif_out_map_player(server, ai, 1, 0) == false)
            ai->x += 1;
    }
    if (ai->direction == WEST){
        if (verif_out_map_player(server, ai, -1, 0) == false)
            ai->x -= 1;
    }
    return "ok";
}

char *player_turns_right(ai_stats_t *ai)
{
    if (ai->direction == WEST) {
        ai->direction = NORTH;
        return "ok";
    }
    ai->direction += 2;
    return "ok";
}

char *player_turns_left(ai_stats_t *ai)
{
    if (ai->direction == NORTH) {
        ai->direction = WEST;
        return "ok";
    }
    ai->direction -= 2;
    return "ok";
}

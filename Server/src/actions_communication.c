/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** actions_communication
*/

#include "actions_communication.h"

/* just to avoid 'unused variable'
 *
 * the real logic is to regroup ai in one same point but we
 *  can't a this time
 *
*/
char *player_plays_broadcast(ai_stats_t *ai, char *text)
{
    int position_x = ai->x;
    int position_y = ai->y;

    printf("%d,%d %s\n", position_x, position_y, text);
    return "ok";
}

char *death_of_player(ai_stats_t *ai)
{
    ai->is_alive = false;
    return "dead";
}

char *can_player_takes_items(ai_stats_t *ai, map_t *map)
{
    ressources_t tile = map->tiles[ai->y][ai->x];
    bool empty = true;

    for (int i = 0; i < 7; i++){
        if (tile.resources[i] > 0) {
            empty = false;
            break;
        }
    }
    if (empty)
        return "ko";
    // possibility to add the item in the players inventory here ?
    // subject pretty blur about it
    return "ok";
}

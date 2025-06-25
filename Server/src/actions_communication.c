/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** actions_communication
*/

#include "actions_communication.h"

#include <unistd.h>

#include "get_signal_direction.h"

/* just to avoid 'unused variable'
 *
 * the real logic is to regroup ai in one same point but we
 *  can't a this time
 *
*/
char *player_plays_broadcast(ai_stats_t *ai, char *text, server_t *server)
{
    // int position_x = ai->x;
    // int position_y = ai->y;

    for (poll_handling_t *tmp = server->poll_list; tmp; tmp = tmp->next)
    {
        if (!tmp->player || tmp->player->id == ai->id || strcmp(tmp->player->team_name, "GRAPHIC") == 0)
            continue;
        int a = snprintf(NULL, 0, "message %d, %s\n", get_signal_direction(ai, tmp->player, server), text);
        char *str = my_malloc(a + 1);
        snprintf(str, a + 1, "message %d, %s\n", get_signal_direction(ai, tmp->player, server), text);
        write(tmp->poll_fd.fd, str, strlen(str));
    }
    // printf("%d,%d %s\n", position_x, position_y, text);
    return "ok\n";
}

char *death_of_player(ai_stats_t *ai)
{
    ai->is_alive = false;
    return "dead\n";
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
        return "ko\n";
    // possibility to add the item in the players inventory here ?
    // subject pretty blur about it
    return "ok\n";
}

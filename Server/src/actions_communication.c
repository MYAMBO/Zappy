/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** actions_communication
*/

#include "actions_communication.h"

#include <unistd.h>

#include "actions_protocol.h"
#include "get_signal_direction.h"
#include "utils.h"

/* just to avoid 'unused variable'
 *
 * the real logic is to regroup ai in one same point but we
 *  can't a this time
 *
*/
char *player_plays_broadcast(ai_stats_t *ai, char *text, server_t *server)
{
    int a;
    char *str;

    for (poll_handling_t *tmp = server->poll_list; tmp; tmp = tmp->next) {
        if (!tmp->player || !tmp->player->connected || tmp->player->id == ai->id ||
            strcmp(tmp->player->team_name, "GRAPHIC") == 0)
            continue;
        a = snprintf(NULL, 0, "message %d, %s\n",
            get_signal_direction(ai, tmp->player, server), text);
        str = my_malloc(a + 1);
        if (!str)
            return NULL;
        snprintf(str, a + 1, "message %d, %s\n",
            get_signal_direction(ai, tmp->player, server), text);
        write(tmp->poll_fd.fd, str, strlen(str));
    }
    return "ok\n";
}

static bool increment_ai_inventory(ai_stats_t *ai, map_t *map,
    int i, server_t *server)
{
    if (map->tiles[ai->y][ai->x].resources[i] <= 0)
        return false;
    map->tiles[ai->y][ai->x].resources[i]--;
    server->current_res[i]--;
    if (i == 0){
        ai->life += 126;
        return true;
    }
    ai->inventory.resources[i]++;
    return true;
}

static bool increment_map_tile(ai_stats_t *ai, map_t *map,
    int i, server_t *server)
{
    if (ai->inventory.resources[i] <= 0)
        return false;
    ai->inventory.resources[i]--;
    map->tiles[ai->y][ai->x].resources[i]++;
    server->current_res[i]++;
    return true;
}

static int get_ressources_index(char *item)
{
    int i = -1;

    if (item == NULL)
        return -1;
    if (strcmp(item, "food") == 0)
        i = 0;
    if (strcmp(item, "linemate") == 0)
        i = 1;
    if (strcmp(item, "deraumere") == 0)
        i = 2;
    if (strcmp(item, "sibur") == 0)
        i = 3;
    if (strcmp(item, "mendiane") == 0)
        i = 4;
    if (strcmp(item, "phiras") == 0)
        i = 5;
    if (strcmp(item, "thystame") == 0)
        i = 6;
    return i;
}

char *can_player_takes_items(ai_stats_t *ai, map_t *map,
    char *item, server_t *server)
{
    char *str;
    int i = 0;

    i = get_ressources_index(item);
    if (i == -1)
        return "ko\n";
    if (!increment_ai_inventory(ai, map, i, server))
        return "ko\n";
    str = player_ressources_collecting(ai, i);
    if (send_message_graphic(server, str) == FAILURE)
        return NULL;
    return "ok\n";
}

char *can_player_drops_items(ai_stats_t *ai, map_t *map,
    char *item, server_t *server)
{
    char *str;
    int i = 0;

    i = get_ressources_index(item);
    if (i == -1)
        return "ko\n";
    if (!increment_map_tile(ai, map, i, server))
        return "ko\n";
    str = player_ressources_dropping(ai, i);
    if (send_message_graphic(server, str) == FAILURE)
        return NULL;
    return "ok\n";
}

char *get_slot_remaining(ai_stats_t *ai, server_t *server)
{
    int found = -1;
    int alloc = 0;
    char *result = NULL;

    for (int i = 0; server->team_names[i] != NULL; i++){
        if (strcmp(server->team_names[i]->name, ai->team_name) == 0) {
            found = i;
            break;
        }
    }
    alloc = snprintf(NULL, 0,
        "%d\n", server->team_names[found]->slots_remaining);
    result = my_malloc(alloc + 1);
    if (!result)
        return NULL;
    snprintf(result, alloc + 1,
        "%d\n", server->team_names[found]->slots_remaining);
    return result;
}

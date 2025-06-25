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

static bool increment_ai_inventory(ai_stats_t *ai, map_t *map, int i)
{
    if (map->tiles[ai->y][ai->x].resources[i] <= 0)
        return false;
    map->tiles[ai->y][ai->x].resources[i]--;
    if (i == 0)
        ai->nb_food++;
    if (i == 1)
        ai->nb_linemate++;
    if (i == 2)
        ai->nb_deraumere++;
    if (i == 3)
        ai->nb_sibur++;
    if (i == 4)
        ai->nb_mendiane++;
    if (i == 5)
        ai->nb_phiras++;
    if (i == 6)
        ai->nb_thystame++;
    return true;
}

static bool increment_map_tile(ai_stats_t *ai, map_t *map, int i)
{
    int *inventory[7] = {
            &ai->nb_food,
            &ai->nb_linemate,
            &ai->nb_deraumere,
            &ai->nb_sibur,
            &ai->nb_mendiane,
            &ai->nb_phiras,
            &ai->nb_thystame
    };

    if (*inventory[i] <= 0)
        return false;
    (*inventory[i])--;
    map->tiles[ai->y][ai->x].resources[i]++;
    return true;
}

static int get_ressources_index(char *item)
{
    int i = -1;

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

char *can_player_takes_items(ai_stats_t *ai, map_t *map, char *item)
{
    int i = 0;

    i = get_ressources_index(item);
    if (i == -1)
        return "ko\n";
    if (!increment_ai_inventory(ai, map, i))
        return "ko\n";
    return "ok\n";
}

char *can_player_drops_items(ai_stats_t *ai, map_t *map, char *item)
{
    int i = 0;

    i = get_ressources_index(item);
    if (i == -1)
        return "ko\n";
    if (!increment_map_tile(ai, map, i))
        return "ko\n";
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

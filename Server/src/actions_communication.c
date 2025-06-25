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
    return "ok\n";
}

char *death_of_player(ai_stats_t *ai)
{
    ai->is_alive = false;
    return "dead\n";
}

static bool parse_valid_ressources(char *item)
{
    if (strcmp("food", item) == 0 || strcmp("linemate", item) == 0
        || strcmp("deraumere", item) == 0 || strcmp("sibur", item) == 0
        || strcmp("mendiane", item) == 0 || strcmp("phiras", item) == 0
        || strcmp("thystame", item) == 0)
        return true;
    else
        return false;
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

static int can_take_one_ressources(char *item)
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

    printf("%d\n", map->tiles[ai->y][ai->x].resources[0]);
    printf("%d\n", ai->nb_food);

    if (!parse_valid_ressources(item))
        return "ko\n";
    i = can_take_one_ressources(item);
    if (i == -1)
        return "ko\n";
    if (!increment_ai_inventory(ai, map, i))
        return "ko\n";
    return "ok\n";
}

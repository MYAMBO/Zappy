/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** incantation_communication
*/

#include "incantation_communication.h"

static bool has_required_rock(map_t *map, ai_stats_t *lead)
{
    int requirements[7][6] = {
            {1, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0},
            {2, 0, 1, 0, 2, 0},
            {1, 1, 2, 0, 1, 0},
            {1, 2, 1, 3, 0, 0},
            {1, 2, 3, 0, 1, 0},
            {2, 2, 2, 2, 2, 1}
    };
    ressources_t tile = map->tiles[lead->y][lead->x];

    for (int i = 0; i < 6; i++) {
        if (tile.resources[i + 1] < requirements[lead->level - 1][i])
            return false;
    }
    return true;
}

static int required_player_count(int level)
{
    switch (level) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 2;
        case 4:
            return 4;
        case 5:
            return 4;
        case 6:
            return 6;
        case 7:
            return 6;
        default:
            return 0;
    }
}

static bool verif_players_stats(poll_handling_t *players,
    ai_stats_t *lead, map_t *map)
{
    int count = 0;

    for (poll_handling_t *poll = players; poll != NULL; poll = poll->next){
        if (!poll->player->is_alive)
            continue;
        if (poll->player->level == lead->level &&
            poll->player->x == lead->x &&
            poll->player->y == lead->y) {
            count++;
            poll->player->in_incantation = true;
        }
    }
    if (count < required_player_count(lead->level))
        return false;
    if (!has_required_rock(map, lead))
        return false;
    return true;
}

char *start_incantation(ai_stats_t *lead, poll_handling_t *players, map_t *map)
{
    int alloc = snprintf(NULL, 0,
        "Elevation underway\nCurrent level: %d\n", lead->level);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return "ko\n";
    if (!verif_players_stats(players, lead, map))
        return "ko\n";
    snprintf(result, alloc + 1,
        "Elevation underway\nCurrent level: %d\n", lead->level);
    return result;
}

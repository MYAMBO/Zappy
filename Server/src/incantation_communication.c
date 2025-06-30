/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** incantation_communication
*/

#include "incantation_communication.h"

#include "incantation_list.h"

static int get_incantation_id(void)
{
    static int id = -1;

    return id++;
}

static bool has_required_rock(map_t *map, ai_stats_t *lead)
{
    return true;
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

static bool has_required_rock_end(map_t *map, int x, int y, int level)
{
    return true;
    int requirements[7][6] = {
        {1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
        {2, 0, 1, 0, 2, 0},
        {1, 1, 2, 0, 1, 0},
        {1, 2, 1, 3, 0, 0},
        {1, 2, 3, 0, 1, 0},
        {2, 2, 2, 2, 2, 1}
    };
    ressources_t tile = map->tiles[y][x];

    for (int i = 0; i < 6; i++) {
        if (tile.resources[i + 1] < requirements[level - 1][i])
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

static int verif_players_stats(server_t *server,
    ai_stats_t *lead, map_t *map)
{
    int count = 0;

    for (poll_handling_t *poll = server->poll_list; poll != NULL; poll = poll->next){
        if (!poll->player || strcmp(poll->player->team_name, "GRAPHIC") == 0)
            continue;
        if (poll->player->level == lead->level &&
            poll->player->x == lead->x &&
            poll->player->y == lead->y)
            count++;
    }
    if (count < required_player_count(lead->level))
        return 1;
    if (!has_required_rock(map, lead))
        return 1;
    int index = get_incantation_id();
    if (add_incantation(&server->incantation_list, index, server->tick, (int[3]){lead->x, lead->y, lead->level}) == FAILURE)
        return FAILURE;
    for (poll_handling_t *poll = server->poll_list; poll != NULL; poll = poll->next){
        if (!poll->player || strcmp(poll->player->team_name, "GRAPHIC") == 0)
            continue;
        if (poll->player->level == lead->level &&
            poll->player->x == lead->x &&
            poll->player->y == lead->y)
            poll->player->in_incantation = index;
    }
    printf("Here\n");

    return SUCCESS;
}

static int verif_players_stats_end(server_t *server,
    map_t *map)
{
    int count = 0;

    for (poll_handling_t *poll = server->poll_list; poll != NULL; poll = poll->next){
        if (!poll->player || strcmp(poll->player->team_name, "GRAPHIC") == 0)
            continue;
        if (poll->player->level == server->incantation_list[0].level_base &&
            poll->player->x == server->incantation_list[0].x &&
            poll->player->y == server->incantation_list[0].y)
            count++;
    }
    if (count < required_player_count(server->incantation_list[0].level_base))
        return 1;
    if (!has_required_rock_end(map, server->incantation_list[0].x, server->incantation_list[0].y, server->incantation_list[0].level_base))
        return 1;
    for (poll_handling_t *poll = server->poll_list; poll != NULL; poll = poll->next){
        if (!poll->player || strcmp(poll->player->team_name, "GRAPHIC") == 0)
            continue;
        if (poll->player->in_incantation == server->incantation_list[0].incantation_nb)
            poll->player->in_incantation = -1;
    }

    return SUCCESS;
}

char *start_incantation(ai_stats_t *lead, server_t *server, map_t *map)
{
    printf("into start\n");

    int val = verif_players_stats(server, lead, map);
    if (val == 1)
        return "ko\n";
    if (val == 84)
        return NULL;

    return "ok\n";
}

char *end_incantation(server_t *server, map_t *map)
{
    int alloc = snprintf(NULL, 0,
       "Elevation underway\nCurrent level: %d\n", server->incantation_list[0].level_base);
    char *result = my_malloc(alloc + 1);

    printf("into end\n");
    if (!result)
        return NULL;
    int val = verif_players_stats_end(server, map);
    if (val == 1)
        return "ko\n";
    if (val == 84)
        return NULL;
    snprintf(result, alloc + 1,
        "Elevation underway\nCurrent level: %d\n", server->incantation_list[0].level_base);
    return result;
}

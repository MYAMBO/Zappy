/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** look_around_communication
*/


#include "look_around_communication.h"

static tile_info_t calculate_tile_info(tile_context_t *ctx)
{
    tile_info_t info = {0, 0};
    char *names[] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};
    int count = 0;

    for (int i = 0; i < 7; i++) {
        count = ctx->map->tiles[ctx->y][ctx->x].resources[i];
        info.total_words += count;
        info.total_len += count * (strlen(names[i]) + 1);
    }
    for (poll_handling_t *tmp = ctx->players; tmp; tmp = tmp->next) {
        if (tmp->player && tmp->player->x == ctx->x &&
            tmp->player->y == ctx->y) {
            info.total_words++;
            info.total_len += strlen("player") + 1;
        }
    }
    return info;
}

static void fill_tile_string(char *result, tile_context_t *ctx)
{
    char *names[] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};
    int offset = 0;
    int count = 0;

    for (int i = 0; i < 7; i++) {
        count = ctx->map->tiles[ctx->y][ctx->x].resources[i];
        for (int j = 0; j < count; j++)
            offset += snprintf(result + offset,
                1000 - offset, "%s ", names[i]);
    }
    for (poll_handling_t *tmp = ctx->players; tmp; tmp = tmp->next) {
        if (tmp->player && tmp->player->x == ctx->x && tmp->player->y ==
            ctx->y && strcmp(tmp->player->team_name, "GRAPHIC") != 0)
            offset += snprintf(result + offset, 1000 - offset,
                "player ");
    }
    if (offset > 0 && result[offset - 1] == ' ')
        result[offset - 1] = '\0';
    result[offset] = '\0';
}

static char *get_tile_description(map_t *map,
    poll_handling_t *players, int x, int y)
{
    tile_context_t ctx = {map, players, x, y};
    tile_info_t info = calculate_tile_info(&ctx);
    char *result = NULL;
    char *empty = NULL;

    if (info.total_words == 0) {
        empty = my_malloc(1);
        if (!empty)
            return NULL;
        empty[0] = '\0';
        return empty;
    }
    result = my_malloc(info.total_len + 1);
    if (!result)
        return NULL;
    fill_tile_string(result, &ctx);
    return result;
}

char *build_lookaround_result(char **tiles,
    size_t tile_count, size_t total_len)
{
    char *res = my_malloc(total_len + 1);

    if (!res)
        return NULL;
    strcpy(res, "[");
    for (size_t i = 0; i < tile_count; i++) {
        strcat(res, tiles[i]);
        if (i < tile_count - 1)
            strcat(res, ",");
    }
    strcat(res, "]\n");
    return res;
}

static bool fill_tile_line(look_context_t *ctx, fill_tile_info_t *info, int d)
{
    int x = 0;
    int y = 0;
    char *desc = NULL;

    for (int p = -d; p <= d; p++) {
        x = (ctx->ai->x + get_dx(ctx->ai->direction, d, p)
            + ctx->map->width) % ctx->map->width;
        y = (ctx->ai->y + get_dy(ctx->ai->direction, d, p)
            + ctx->map->height) % ctx->map->height;
        desc = get_tile_description(ctx->map, ctx->players, x, y);
        if (!desc)
            desc = my_malloc(1);
        if (!desc)
            return false;
        info->tiles[*(info->tile_count)] = desc;
        (*(info->tile_count))++;
        *(info->total_len) += strlen(desc) + 1;
    }
    return true;
}

bool fill_tile_descriptions(look_context_t *ctx, char **tiles,
    size_t *tile_count, size_t *total_len)
{
    fill_tile_info_t info = {
            .tiles = tiles,
            .tile_count = tile_count,
            .total_len = total_len
    };

    *tile_count = 0;
    for (int d = 0; d <= ctx->ai->level; d++) {
        if (!fill_tile_line(ctx, &info, d))
            return false;
    }
    return true;
}

char *player_looks_around(ai_stats_t *ai, poll_handling_t *players, map_t *map)
{
    size_t tile_count = count_visible_tiles(ai->level);
    char **tiles = my_malloc(sizeof(char *) * tile_count);
    size_t total_len = 2;
    char *result = NULL;
    look_context_t ctx = {ai, players, map};

    if (!tiles)
        return NULL;
    if (!fill_tile_descriptions(&ctx, tiles, &tile_count, &total_len)) {
        free_tiles(tiles, tile_count);
        return NULL;
    }
    result = build_lookaround_result(tiles, tile_count, total_len);
    free_tiles(tiles, tile_count);
    return result;
}

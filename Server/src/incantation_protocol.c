/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** incantation_protocol
*/

#include "incantation_protocol.h"

char *start_incantation_protocol(ai_stats_t *lead, ai_stats_t *rest[])
{
    int alloc = snprintf(NULL, 0, "pic %d %d %d #%d",
        lead->x, lead->y, lead->level, lead->id);
    char *result = NULL;
    int offset = 0;

    for (int i = 0; rest != NULL && rest[i] != NULL; i++)
        alloc += snprintf(NULL, 0, " #%d", rest[i]->id);
    alloc += snprintf(NULL, 0, "\n");
    result = my_malloc(alloc + 1);
    if (!result)
        return NULL;
    offset += sprintf(result + offset, "pic %d %d %d #%d", lead->x,
        lead->y, lead->level, lead->id);
    for (int i = 0; rest != NULL && rest[i] != NULL; i++)
        offset += sprintf(result + offset, " #%d", rest[i]->id);
    sprintf(result + offset, "\n");
    return result;
}

char *end_incantation_protocol(ai_stats_t *lead, bool status)
{
    char *incantation_status = NULL;
    int alloc = 0;
    char *result = NULL;

    if (status)
        incantation_status = "success";
    else
        incantation_status = "failed";
    alloc = snprintf(NULL, 0,
        "pie %d %d %s", lead->x, lead->y, incantation_status);
    result = my_malloc(alloc + 1);
    if (!result)
        return NULL;
    snprintf(result, alloc + 1,
        "pie %d %d %s", lead->x, lead->y, incantation_status);
    return result;
}

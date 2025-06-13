/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** technical_protocol
*/


#include "technical_protocol.h"


char *get_server_message(char *message)
{
    int alloc = snprintf(NULL, 0, "smg %s\n", message);
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "smg %s\n", message);
    return result;
}

char *get_unknown_command(void)
{
    int alloc = snprintf(NULL, 0, "suc\n");
    char *result = my_malloc(alloc + 1);

    if (!result)
        return NULL;
    snprintf(result, alloc + 1, "suc\n");
    return result;
}

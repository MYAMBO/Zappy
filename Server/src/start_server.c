/*
** EPITECH PROJECT, 2025
** start_server.c
** File description:
** start_server.c
** created and edited by antoiix.
** All rights reserved
*/

#include <stdio.h>

#include "server.h"
#include "garbage.h"

int call_poll(server_t *server)
{
    struct pollfd poll_list[MAX_CLIENT] = {0};
    int poll_val;

    convert_poll_handling(server->poll_list, poll_list, server->poll_count);
    poll_val = poll(poll_list, server->poll_count, -1);
    convert_poll_handling_reverse(server->poll_list,
        poll_list, server->poll_count);
    return poll_val;
}

static void init_entry_table(entry_t **table)
{
    *table = my_malloc(sizeof(entry_t) * 2);
    (*table)[0].command = NULL;
    (*table)[0].function = NULL;
}

int start_server(server_t *server)
{
    int poll_val;
    entry_t *table = NULL;

    init_entry_table(&table);
    while (1) {
        poll_val = call_poll(server);
        if (poll_val == -1)
            return FAILURE;
        if (poll_val == 0)
            continue;
        handle_event(server);
    }
}

/*
** EPITECH PROJECT, 2025
** start_server.c
** File description:
** start_server.c
** created and edited by antoiix.
** All rights reserved
*/

#include <stdio.h>
#include <time.h>
#include "command_exec_handler.h"
#include "server.h"
#include "garbage.h"
#include "time_handler.h"

int call_poll(server_t *server)
{
    struct pollfd poll_list[MAX_CLIENT] = {0};
    int poll_val;

    convert_poll_handling(server->poll_list, poll_list, server->poll_count);
    poll_val = poll(poll_list, server->poll_count, 0);
    convert_poll_handling_reverse(server->poll_list,
        poll_list, server->poll_count);
    return poll_val;
}

static int exec_time_exec_handler(server_t *server)
{
    increase_tick(server);
    for (poll_handling_t *node = server->poll_list; node != NULL;
        node = node->next) {
        command_exec_queue(node, server->tick);
        if (launch_command_exec(node, server->tick, server) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int start_server(server_t *server)
{
    int poll_val;

    server->base_time = clock();
    while (*is_running() == 1) {
        if (exec_time_exec_handler(server) == FAILURE)
            return FAILURE;
        if (server->team_names[0]->nb_slots == 0 &&
            add_slot(server->team_names[0]) == FAILURE)
            return FAILURE;
        poll_val = call_poll(server);
        if (poll_val == -1)
            return FAILURE;
        if (poll_val == 0)
            continue;
        if (handle_event(server) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

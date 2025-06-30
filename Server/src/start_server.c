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
#include <unistd.h>
#include "commands.h"
#include "command_exec_handler.h"
#include "server.h"
#include "garbage.h"
#include "generate_ressources.h"
#include "incantation_list.h"
#include "player_informations_protocol.h"
#include "slot_handler.h"
#include "time_handler.h"
#include "utils.h"
#include "actions_protocol.h"
#include "time_exec_handler.h"

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

static int call_end_indentation(server_t *server, incantation_list_t *tmp)
{
    if (server->tick >= tmp->tick_end) {
        if (end_incantation_command(server, NULL, NULL) == FAILURE)
            return FAILURE;
        pop_incantation(&server->incantation_list);
    }
    return SUCCESS;
}

int incantation_check(server_t *server)
{
    incantation_list_t *next = NULL;

    for (incantation_list_t *tmp = server->incantation_list; tmp; tmp = next) {
        next = tmp->next;
        if (call_end_indentation(server, tmp) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

static int exec_time_exec_handler(server_t *server)
{
    if (server->regenerate_time == -1 || server->regenerate_time + 20000 <=
        server->tick) {
        server->regenerate_time = server->tick;
        generate_all_ressources(server);
    }
    if (increase_tick(server) == false)
        return SUCCESS;
    if (incantation_check(server) == FAILURE)
        return FAILURE;
    if (time_exec_handler_exec(server) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

static int check_win_condition(server_t *server, int count, int i)
{
    char *msg = NULL;

    if (count >= 6) {
        msg = end_of_game(server->team_names[i]->name);
        if (msg == NULL)
            return FAILURE;
        if (send_message_graphic(server, msg) == FAILURE)
            return FAILURE;
        return 1;
    }
    return SUCCESS;
}

static void search_players_max(server_t *server, int *count, int i)
{
    poll_handling_t *node = NULL;

    for (slot_t *slot = server->team_names[i]->slots; slot != NULL;
            slot = slot->next) {
        node = search_player_node(slot->id_user, server);
        if (node == NULL)
            continue;
        if (node->player->level == 8)
            (*count)++;
    }
}

static int win_condition(server_t *server)
{
    int count = 0;

    for (int i = 0; server->team_names[i]; i++) {
        count = 0;
        search_players_max(server, &count, i);
        if (check_win_condition(server, count, i) == 1)
            return 1;
        if (check_win_condition(server, count, i) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

static int loop_iteration(server_t *server, int *poll_val, int *win_val)
{
    if (*win_val != 1) {
        *win_val = win_condition(server);
        if (*win_val == FAILURE)
            return FAILURE;
    }
    if (*win_val == 1)
        return SUCCESS;
    if (exec_time_exec_handler(server) == FAILURE)
        return FAILURE;
    *poll_val = call_poll(server);
    if (*poll_val == -1)
        return FAILURE;
    if (*poll_val == 0)
        return SUCCESS;
    if (handle_event(server) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

static int loop_start_server(server_t *server, int poll_val, int win_val)
{
    while (*is_running()) {
        if (server->team_names[0]->nb_slots == 0 &&
            add_slot(server->team_names[0],
            (int[2]){-1, -1}, -1, server) == FAILURE)
            return FAILURE;
        if (loop_iteration(server, &poll_val, &win_val) == FAILURE)
            return FAILURE;
        if (win_val == 1 || poll_val == 0)
            continue;
    }
    return SUCCESS;
}

int start_server(server_t *server)
{
    int poll_val = 0;
    int win_val = 0;

    server->base_time = clock();
    if (loop_start_server(server, poll_val, win_val) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

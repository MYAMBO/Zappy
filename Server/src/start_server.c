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

int incantation_check(server_t *server)
{
    incantation_list_t *next = NULL;

    for (incantation_list_t *tmp = server->incantation_list; tmp; tmp = next) {
        next = tmp->next;
        if (server->tick >= tmp->tick_end) {
            printf("entered with %d and %d\n", server->tick, tmp->tick_end);
            if (end_incantation_command(server, NULL, NULL) == FAILURE)
                return FAILURE;
            pop_incantation(&server->incantation_list);
        }
    }
    return SUCCESS;
}

static int exec_time_exec_handler(server_t *server)
{
    poll_handling_t *next = NULL;

    if (server->regenerate_time == -1 || server->regenerate_time + 20000 <=
        server->tick) {
        server->regenerate_time = server->tick;
        generate_all_ressources(server);
    }
    if (increase_tick(server) == false)
        return SUCCESS;
    if (incantation_check(server) == FAILURE)
        return FAILURE;
    for (poll_handling_t *node = server->poll_list; node != NULL;
        node = next) {
        next = node->next;
        if (node->player && (strcmp(node->player->team_name, "GRAPHIC") == 0
            || node->player->connected == false))
            continue;
        if (node->player && node->player->last_life == -1) {
            node->player->last_life = server->tick;
        }
        if (node->player && node->player->last_life + 1000 < server->tick) {
            node->player->life--;
            node->player->last_life = server->tick;
        }
        if (node->player && node->player->life <= 0) {
            write(node->player->fd, "dead\n", strlen("dead\n"));
            char *str = player_death(node->player);
            if (str == NULL)
                return FAILURE;
            if (send_message_graphic(server, str) == FAILURE)
                return FAILURE;
            slot_table_t *table = NULL;
            for (int i = 0; server->team_names[i]; i++) {
                if (strcmp(server->team_names[i]->name,
                    node->player->team_name) == 0)
                    table = server->team_names[i];
            }
            if (table == NULL)
                return FAILURE;
            if (disconnect_player(&table, node->player->id) == FAILURE)
                return FAILURE;
            close(node->player->fd);
            remove_node_poll_handling(&server->poll_list, node->player->fd);
            continue;
        }
        command_exec_queue(node, server->tick);
        if (launch_command_exec(node, server->tick, server) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

static int win_condition(server_t *server)
{
    int count = 0;

    for (int i = 0; server->team_names[i]; i++) {
        count = 0;
        for (slot_t *slot = server->team_names[i]->slots; slot != NULL; slot = slot->next) {
            poll_handling_t *node = search_player_node(slot->id_user, server);
            if (node == NULL)
                continue;
            if (node->player->level == 8)
                count++;
        }
        if (count >= 6) {
            char *msg = end_of_game(server->team_names[i]->name);
            if (msg == NULL)
                return FAILURE;
            if (send_message_graphic(server, msg) == FAILURE)
                return FAILURE;
            return 1;
        }
    }
    return SUCCESS;
}

static int loop_start_server(server_t *server)
{

}

int start_server(server_t *server)
{
    int poll_val;
    int win_val = 0;

    server->base_time = clock();
    while (*is_running() == 1) {
        if (win_val == 1)
            continue;
        win_val = win_condition(server);
        if (win_val == FAILURE)
            return FAILURE;
        if (win_val == 1)
            continue;
        if (exec_time_exec_handler(server) == FAILURE)
            return FAILURE;
        if (server->team_names[0]->nb_slots == 0 &&
            add_slot(server->team_names[0], (int[2]){-1, -1}, -1, server) == FAILURE)
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

/*
** EPITECH PROJECT, 2025
** time_exec_handler.c
** File description:
** time_exec_handler.c
** created and edited by antoiix.
** All rights reserved
*/

#include "time_exec_handler.h"

static int disconnect_from_slot(server_t *server, poll_handling_t *node)
{
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
    return SUCCESS;
}

static int dead_handling(server_t *server, poll_handling_t *node)
{
    char *str = NULL;

    if (node->player && node->player->life <= 0) {
        write(node->player->fd, "dead\n", strlen("dead\n"));
        str = player_death(node->player);
        if (str == NULL)
            return FAILURE;
        if (send_message_graphic(server, str) == FAILURE)
            return FAILURE;
        if (disconnect_from_slot(server, node) == FAILURE)
            return FAILURE;
        close(node->player->fd);
        remove_node_poll_handling(&server->poll_list, node->player->fd);
        return 1;
    }
    return SUCCESS;
}

static int decrement_time(server_t *server, poll_handling_t *node)
{
    if (node->player && (strcmp(node->player->team_name, "GRAPHIC") == 0
            || node->player->connected == false))
        return 1;
    if (node->player && node->player->last_life == -1)
        node->player->last_life = server->tick;
    if (node->player && node->player->last_life + 1000 < server->tick) {
        node->player->life--;
        node->player->last_life = server->tick;
    }
    return SUCCESS;
}

int time_exec_handler_exec(server_t *server)
{
    poll_handling_t *next = NULL;
    int val;

    for (poll_handling_t *node = server->poll_list; node != NULL;
        node = next) {
        next = node->next;
        if (decrement_time(server, node) == 1)
            continue;
        val = dead_handling(server, node);
        if (val == FAILURE)
            return FAILURE;
        if (val == 1)
            continue;
        command_exec_queue(node, server->tick);
        if (launch_command_exec(node, server->tick, server) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

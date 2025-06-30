/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** command_incantation
*/

#include "commands.h"
#include "poll_handling.h"
#include "struct.h"
#include "utils.h"
#include "incantation_communication.h"
#include "incantation_protocol.h"
#include "unistd.h"
#include <stdbool.h>
#include <string.h>
#include "send_init_graphic.h"

static int count_incant(server_t *server, int id, poll_handling_t *node)
{
    int count = 0;

    for (poll_handling_t *tmp = server->poll_list; tmp; tmp = tmp->next) {
        if (!tmp->player || strcmp(tmp->player->team_name, "GRAPHIC") == 0)
            continue;
        if (tmp->player && tmp->player->in_incantation == id &&
            tmp->player->id != node->player->id)
            count++;
    }
    return count;
}

static int get_other_incantation_suite(server_t *server, ai_stats_t **list,
    poll_handling_t *node)
{
    char *str = start_incantation_protocol(node->player, list);

    my_free(list);
    if (!str)
        return FAILURE;
    if (send_message_graphic(server, str) == FAILURE) {
        my_free(str);
        return FAILURE;
    }
    my_free(str);
    return SUCCESS;
}

static int get_other_incantation(server_t *server,
    int id, poll_handling_t *node)
{
    int tmp_count = 0;
    int count = count_incant(server, id, node);
    ai_stats_t **list = my_malloc(sizeof(ai_stats_t *) * (count + 1));

    if (!list)
        return FAILURE;
    for (int i = 0; i <= count; i++)
        list[i] = NULL;
    for (poll_handling_t *tmp = server->poll_list; tmp; tmp = tmp->next) {
        if (!tmp->player || strcmp(tmp->player->team_name, "GRAPHIC") == 0)
            continue;
        if (tmp->player && tmp->player->in_incantation ==
            id && tmp->player->id != node->player->id) {
            list[tmp_count] = tmp->player;
            tmp_count++;
        }
    }
    return get_other_incantation_suite(server, list, node);
}

int incantation_command(server_t *server,
    poll_handling_t *node, char **args)
{
    char *str = NULL;

    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    str = start_incantation(node->player, server, server->map);
    if (!str)
        return FAILURE;
    if (strcmp(str, "ko\n") == 0)
        write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    if (get_other_incantation(server,
        node->player->in_incantation, node) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

void end_incantation_command_suite(server_t *server, char *str)
{
    unsigned long len = strlen(str);

    for (poll_handling_t *poll = server->poll_list; poll; poll = poll->next) {
        if (!poll->player || strcmp(poll->player->team_name, "GRAPHIC") == 0 ||
            poll->player->in_incantation !=
            server->incantation_list[0].incantation_nb)
            continue;
        poll->player->in_incantation = -1;
        write(poll->player->fd, str, len);
        if (strcmp(str, "ko\n") != 0)
            poll->player->level++;
    }
}

int end_incantation_command(server_t *server, poll_handling_t *node,
    char **args)
{
    char *str = NULL;
    char *msg = NULL;
    bool status = false;

    (void)node;
    (void)args;
    str = end_incantation(server, server->map);
    if (!str)
        return FAILURE;
    status = strcmp(str, "ko\n") == 0 ? false : true;
    msg = end_incantation_protocol(server->incantation_list, status);
    if (!msg || send_message_graphic(server, msg) == FAILURE)
        return FAILURE;
    my_free(msg);
    end_incantation_command_suite(server, str);
    if (send_info_user(server, node) == FAILURE)
        return FAILURE;
    my_free(str);
    return SUCCESS;
}

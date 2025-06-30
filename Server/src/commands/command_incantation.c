/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** command_incantation
*/

#include "commands.h"
#include "utils.h"
#include "incantation_communication.h"
#include "incantation_protocol.h"
#include "unistd.h"

static int count_incant(server_t *server, int id, poll_handling_t *node)
{
    int count = 0;
    for (poll_handling_t *tmp = server->poll_list; tmp; tmp = tmp->next)
    {
        if (!tmp->player || strcmp(tmp->player->team_name, "GRAPHIC") == 0)
            continue;
        if (tmp->player && tmp->player->in_incantation == id && tmp->player->id != node->player->id)
        {
            count++;
        }
    }
    return count;
}

static int get_other_incantation(server_t *server, int id, poll_handling_t *node)
{
    int count = count_incant(server, id, node);
    ai_stats_t **list = NULL;  // Changed to pointer to pointer
    int tmp_count = 0;
    char *str = NULL;

    // Allocate memory for the array of pointers
    list = my_malloc(sizeof(ai_stats_t*) * (count + 1));
    if (!list)
        return FAILURE;

    // Initialize the array with NULL
    for (int i = 0; i <= count; i++)
        list[i] = NULL;

    // Fill the array with player pointers
    for (poll_handling_t *tmp = server->poll_list; tmp; tmp = tmp->next)
    {
        if (!tmp->player || strcmp(tmp->player->team_name, "GRAPHIC") == 0)
            continue;
        if (tmp->player && tmp->player->in_incantation == id && tmp->player->id != node->player->id)
        {
            list[tmp_count] = tmp->player;
            tmp_count++;
        }
    }

    str = start_incantation_protocol(node->player, list);
    if (!str) {
        my_free(list);  // Free the allocated array
        return FAILURE;
    }

    if (send_message_graphic(server, str) == FAILURE) {
        my_free(list);  // Free the allocated array
        my_free(str);
        return FAILURE;
    }

    my_free(list);  // Free the allocated array
    my_free(str);
    return SUCCESS;
}

int incantation_command(server_t *server, poll_handling_t *node, char **args)
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
    if (get_other_incantation(server, node->player->in_incantation, node) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int end_incantation_command(server_t *server, poll_handling_t *node, char **args)
{
    char *str = NULL;
    char *msg = NULL;
    bool status = strcmp(str, "ko\n") == 0 ? false : true;

    (void)node;
    (void)args;
    str = end_incantation(server, server->map);
    printf("lala1\n");
    if (!str)
        return FAILURE;
    msg = end_incantation_protocol(server->incantation_list, status);
    if (!msg)
        return FAILURE;
    if (send_message_graphic(server, msg) == FAILURE)
        return FAILURE;
    my_free(msg);
    printf("lala2\n");
    printf("%s", str);
    for (poll_handling_t *poll = server->poll_list; poll != NULL; poll = poll->next) {
        if (!poll->player || strcmp(poll->player->team_name, "GRAPHIC") == 0)
            continue;
        if (poll->player->in_incantation == server->incantation_list[0].incantation_nb &&
            strcmp(str, "ko\n") == 0) {
            poll->player->in_incantation = -1;
            write(poll->player->fd, str, strlen(str));
        }
        if (poll->player->in_incantation == server->incantation_list[0].incantation_nb &&
            strcmp(str, "ko\n") != 0)
        {
            poll->player->in_incantation = -1;
            poll->player->level++;
            write(poll->player->fd, str, strlen(str));
        }
    }
    my_free(str);
    return SUCCESS;
}
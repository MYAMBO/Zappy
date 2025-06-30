/*
** EPITECH PROJECT, 2025
** send_slot_messages.c
** File description:
** send_slot_messages.c
** created and edited by antoiix.
** All rights reserved
*/

#include "send_slot_messages.h"

static int get_table(server_t *server, poll_handling_t *node)
{
    int i = 0;

    for (i = 0; server->team_names[i] != NULL; i++) {
        if (strcmp(server->team_names[i]->name, node->player->team_name) == 0)
            return i;
    }
    return 0;
}

static int send_egg_connection(server_t *server, poll_handling_t *node)
{
    slot_t *slot = NULL;
    char *str = NULL;
    int i = get_table(server, node);

    for (slot = server->team_names[i]->slots; slot &&
        slot->id_user != node->player->id; slot = slot->next);
    if (!slot)
        return FAILURE;
    str = get_connection_from_egg(slot);
    if (str == NULL)
        return FAILURE;
    if (send_message_graphic(server, str) == FAILURE)
        return FAILURE;
    my_free(str);
    return SUCCESS;
}

static int set_player_connection(server_t *server, poll_handling_t *node)
{
    char *str = player_new_connection(node->player);

    if (str == NULL)
        return FAILURE;
    if (send_message_graphic(server, str) == FAILURE)
        return FAILURE;
    my_free(str);
    if (send_egg_connection(server, node) == FAILURE)
        return FAILURE;
    if (send_map_size_message(server, node) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

static int send_slot_remaining_massages(server_t *server,
    poll_handling_t *node, int i)
{
    int j;
    char *str;

    j = snprintf(NULL, 0, "%d\n",
        server->team_names[i]->slots_remaining);
    str = my_malloc((j + 1) * sizeof(char));
    if (str == NULL)
        return FAILURE;
    sprintf(str, "%d\n", server->team_names[i]->slots_remaining);
    write(node->poll_fd.fd, str, j);
    my_free(str);
    if (strcmp(node->player->team_name, "GRAPHIC") == 0){
        if (send_graphic_init(server, node) == FAILURE)
            return FAILURE;
    } else {
        if (set_player_connection(server, node) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int send_slot_remaining(int *val, server_t *server,
    poll_handling_t *node, char **args)
{
    for (int i = 0; server->team_names[i] != NULL; i++) {
        if (strcmp(args[0], server->team_names[i]->name) != 0)
            continue;
        *val = connect_player(server->team_names[i], node->player);
        if (*val == FAILURE)
            return FAILURE;
        if (*val != 0)
            continue;
        return send_slot_remaining_massages(server, node, i);
    }
    return SUCCESS;
}

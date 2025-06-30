/*
** EPITECH PROJECT, 2025
** send_slots_remaining.c
** File description:
** send_slots_remaining.c
** created and edited by antoiix.
** All rights reserved
*/

#include "send_slots_remaining.h"

static slot_t *browse_team_slots(server_t *server, poll_handling_t *node,
    int i)
{
    slot_t *slot = NULL;

    for (slot = server->team_names[i]->slots;
        slot && slot->id_user != node->player->id; slot = slot->next);
    return slot;
}

int remaining_massages_part_two(poll_handling_t *node,
    char *str, slot_t *slot, server_t *server)
{
    str = player_new_connection(node->player);
    if (str == NULL)
        return FAILURE;
    if (send_message_graphic(server, str) == FAILURE)
        return FAILURE;
    my_free(str);
    for (int i = 0; server->team_names[i] != NULL; i++)
        if (strcmp(server->team_names[i]->name, node->player->team_name) == 0)
            slot = browse_team_slots(server, node, i);
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

int send_slot_remaining_mess(server_t *server, poll_handling_t *node,
    char **str, int i)
{
    int j;

    j = snprintf(NULL, 0, "%d\n",
            server->team_names[i]->slots_remaining);
    *str = my_malloc((j + 1) * sizeof(char));
    if (*str == NULL)
        return FAILURE;
    if (strcmp(node->player->team_name, "GRAPHIC") != 0) {
        sprintf(*str, "%d\n", server->team_names[i]->slots_remaining);
        write(node->poll_fd.fd, *str, j);
    }
    my_free(str);
    return SUCCESS;
}

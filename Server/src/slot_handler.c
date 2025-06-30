/*
** EPITECH PROJECT, 2025
** slot_handler.c
** File description:
** slot_handler.c
** created and edited by antoiix.
** All rights reserved
*/

#include "slot_handler.h"

#include <string.h>

static int get_global_id(void)
{
    static int id = -1;

    id++;
    return id;
}

static slot_t *init_slot(slot_table_t *table, int xy[2], int id_user, server_t *server)
{
    slot_t *slot = my_malloc(sizeof(slot_t));

    if (!slot)
        return NULL;
    slot->global_id = get_global_id();
    slot->id_slot = table->id_slot_current;
    table->id_slot_current = table->id_slot_current + 1;
    slot->id_user = id_user;
    if (xy[0] < 0 || xy[1] < 0) {
        slot->x = rand() % server->map_width;
        slot->y = rand() % server->map_height;
    } else {
        slot->x = xy[0];
        slot->y = xy[1];
    }
    slot->next = NULL;
    return slot;
}

int add_slot(slot_table_t *slot_table, int xy[2], int id_user, server_t *server)
{
    slot_t *slot = init_slot(slot_table, xy, id_user, server);
    slot_t *tmp;

    if (slot == NULL)
        return FAILURE;
    if (slot_table->slots == NULL) {
        slot_table->slots = slot;
        return SUCCESS;
    }
    for (tmp = slot_table->slots; tmp->next; tmp = tmp->next);
    tmp->next = slot;
    slot_table->nb_slots++;
    slot_table->slots_remaining++;
    return SUCCESS;
}

static void handle_node_removing(slot_t *prev, slot_t *node,
    slot_t *next, slot_t **head)
{
    if (prev == NULL)
        *head = next;
    else
        prev->next = next;
    my_free(node);
}

void remove_slot(slot_t **slot_table, int id_slot)
{
    slot_t *node = *slot_table;
    slot_t *prev = NULL;
    slot_t *next;

    while (node != NULL) {
        next = node->next;
        if (node->id_slot == id_slot)
            handle_node_removing(prev, node, next, slot_table);
        else
            prev = node;
        node = next;
    }
}

int connect_player(slot_table_t *slot_table, ai_stats_t *user)
{
    slot_t *slot;

    if (slot_table == NULL || slot_table->slots_remaining == 0 ||
        slot_table->slots == NULL)
        return SUCCESS;
    slot = slot_table->slots;
    while (slot->id_user != -1)
        slot = slot->next;
    slot->id_user = user->id;
    user->x = slot->x;
    user->y = slot->y;
    user->team_name = my_malloc(sizeof(char) *
        (strlen(slot_table->name) + 1));
    if (user->team_name == NULL)
        return FAILURE;
    strcpy(user->team_name, slot_table->name);
    slot_table->slots_remaining--;
    return SUCCESS;
}

static int disconnect_player_helper(slot_table_t **slot_table,
    int id_user, int i)
{
    for (slot_t *slot = slot_table[i]->slots; slot != NULL;
            slot = slot->next) {
        if (slot->id_user == id_user) {
            remove_slot(&slot_table[i]->slots, slot->id_slot);
            slot_table[i]->nb_slots--;
            return SUCCESS;
        }
    }
    return 1;
}

int disconnect_player(slot_table_t **slot_table, int id_user)
{
    int val;

    for (int i = 0; slot_table[i] != NULL; i++) {
        val = disconnect_player_helper(slot_table, id_user, i);
        if (val != 1)
            return val;
    }
    return FAILURE;
}

slot_table_t *create_slot_table(int nb_slots, char *name, server_t *server)
{
    slot_table_t *slot_table = my_malloc(sizeof(slot_table_t));
    int error_num = 0;

    if (!slot_table)
        return NULL;
    slot_table->nb_slots = nb_slots;
    slot_table->name = name;
    slot_table->slots = NULL;
    slot_table->id_slot_current = 0;
    for (int i = 0; i < nb_slots; i++) {
        error_num = add_slot(slot_table, (int[2]){-1, -1}, -1, server);
        if (error_num == FAILURE)
            return NULL;
    }
    slot_table->slots_remaining = nb_slots;
    return slot_table;
}

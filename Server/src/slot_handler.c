/*
** EPITECH PROJECT, 2025
** slot_handler.c
** File description:
** slot_handler.c
** created and edited by antoiix.
** All rights reserved
*/

#include "slot_handler.h"

#include <time.h>

#include "garbage.h"
#include "server.h"


static slot_t *init_slot(slot_table_t *table)
{
    slot_t *slot = my_malloc(sizeof(slot_t));

    if (!slot)
        return NULL;
    slot->id_slot = table->id_slot_current;
    table->id_slot_current = table->id_slot_current + 1;
    slot->id_user = -1;
    slot->next = NULL;
    return slot;
}

int add_slot(slot_table_t *slot_table)
{
    slot_t *slot = init_slot(slot_table);
    slot_t *tmp;

    if (slot == NULL)
        return FAILURE;
    if (slot_table->slots == NULL) {
        slot_table->slots = slot;
        return SUCCESS;
    }
    for (tmp = slot_table->slots; tmp->next; tmp = tmp->next);
    tmp->next = slot;
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

int connect_player(slot_table_t *slot_table, int id_user)
{
    slot_t *slot;

    if (slot_table == NULL || slot_table->slots_remaining == 0 ||
        slot_table->slots == NULL)
        return FAILURE;
    slot = slot_table->slots;
    while (slot->id_user != -1)
        slot = slot->next;
    slot->id_user = id_user;
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

slot_table_t *create_slot_table(int nb_slots, char *name)
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
        error_num = add_slot(slot_table);
        if (error_num == FAILURE)
            return NULL;
    }
    slot_table->slots_remaining = nb_slots;
    return slot_table;
}

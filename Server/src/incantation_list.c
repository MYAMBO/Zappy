/*
** EPITECH PROJECT, 2025
** incantation_list.c
** File description:
** incantation_list.c
** created and edited by antoiix.
** All rights reserved
*/

#include "incantation_list.h"
#include "garbage.h"
#include "server.h"

static incantation_list_t *init_node(int incantation_nb, int tick_actual, int xy_lev[3])
{
    incantation_list_t *tmp = my_malloc(sizeof(incantation_list_t));

    if (tmp == NULL)
        return NULL;
    tmp->incantation_nb = incantation_nb;
    tmp->tick_end = tick_actual + 300000;
    tmp->x = xy_lev[0];
    tmp->y = xy_lev[1];
    tmp->level_base = xy_lev[2];
    tmp->next = NULL;
    return tmp;
}

int add_incantation(incantation_list_t **head, int incantation_nb, int tick_actual, int xy_lev[3])
{
    incantation_list_t *node = init_node(incantation_nb, tick_actual, xy_lev);
    incantation_list_t *tmp;

    if (node == NULL)
        return FAILURE;
    if (*head == NULL) {
        *head = node;
        return SUCCESS;
    }
    for (tmp = *head; tmp->next; tmp = tmp->next);
    tmp->next = node;
    return SUCCESS;
}

void pop_incantation(incantation_list_t **head)
{
    incantation_list_t *tmp = *head;

    if (*head == NULL)
        return;
    *head = tmp->next;
    my_free(tmp);
}

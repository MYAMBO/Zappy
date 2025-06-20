/*
** EPITECH PROJECT, 2025
** garbage.c
** File description:
** garbage.c
** created and edited by antoiix.
** All rights reserved
*/

#include <stdlib.h>
#include "garbage.h"
#include <string.h>

static garbage_t *create_node_garbage(void *ptr)
{
    garbage_t *node = malloc(sizeof(garbage_t));

    if (node == NULL)
        return NULL;
    node->data = ptr;
    node->next = NULL;
    return node;
}

static int append_node_garbage(garbage_t **head, void *data)
{
    garbage_t *new_node = create_node_garbage(data);

    if (new_node == NULL)
        return 84;
    if (*head == NULL)
        *head = new_node;
    else {
        new_node->next = *head;
        *head = new_node;
    }
    return 0;
}

static garbage_t **get_garbage(void)
{
    static garbage_t *head = NULL;

    return &head;
}

void free_garbage(void)
{
    garbage_t **head = get_garbage();
    garbage_t *node = *head;
    garbage_t *next;

    while (node != NULL) {
        next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    *head = NULL;
}

void *my_malloc(size_t size)
{
    garbage_t **head = get_garbage();
    void *pointer = malloc(size);

    if (pointer == NULL)
        return NULL;
    if (append_node_garbage(head, pointer)) {
        free(pointer);
        return NULL;
    }
    memset(pointer, 0, size);
    return pointer;
}

void my_free(void *ptr)
{
    garbage_t **current = get_garbage();
    garbage_t *temp;

    while (*current) {
        if ((*current)->data == ptr) {
            temp = *current;
            *current = (*current)->next;
            free(temp->data);
            free(temp);
            return;
        }
        current = &(*current)->next;
    }
}

void my_free_array(char **ptr)
{
    for (int i = 0; ptr[i] != NULL; i++)
        my_free(ptr[i]);
    my_free(ptr);
}

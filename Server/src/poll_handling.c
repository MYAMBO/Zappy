/*
** EPITECH PROJECT, 2025
** poll_handling.c
** File description:
** poll_handling.c
** created and edited by antoiix.
** All rights reserved
*/

#include "stdio.h"
#include "stdlib.h"
#include "server.h"
#include "garbage.h"
#include "poll_handling.h"
#include <stdio.h>
#include "init_player.h"

poll_handling_t *create_node_poll_handling(int fd, bool create_client)
{
    poll_handling_t *node = my_malloc(sizeof(poll_handling_t));

    if (node == NULL)
        return NULL;
    node->poll_fd.fd = fd;
    node->poll_fd.events = POLLIN;
    node->poll_fd.revents = 0;
    if (create_client) {
        node->player = init_new_player(fd, 0, 0, "TEST");
        if (node->player == NULL)
            return NULL;
    }
    node->next = NULL;
    return node;
}

int append_node_poll_handling(poll_handling_t **head,
    int fd, bool create_client)
{
    poll_handling_t *new_node = create_node_poll_handling(fd, create_client);
    poll_handling_t *node;

    if (new_node == NULL)
        return FAILURE;
    if (*head == NULL)
        *head = new_node;
    else {
        for (node = *head; node->next != NULL; node = node->next);
        node->next = new_node;
    }
    return SUCCESS;
}

static void handle_node_removing(poll_handling_t *prev, poll_handling_t *node,
    poll_handling_t *next, poll_handling_t **head)
{
    if (prev == NULL)
        *head = next;
    else
        prev->next = next;
    if (node->player->tmp_command != NULL)
        my_free(node->player->tmp_command);
    my_free(node->player->team_name);
    my_free(node->player);
    my_free(node);
}

void remove_node_poll_handling(poll_handling_t **head, int fd)
{
    poll_handling_t *node = *head;
    poll_handling_t *prev = NULL;
    poll_handling_t *next;

    while (node != NULL) {
        next = node->next;
        if (node->poll_fd.fd == fd)
            handle_node_removing(prev, node, next, head);
        else
            prev = node;
        node = next;
    }
}

struct pollfd *convert_poll_handling(poll_handling_t *head,
    struct pollfd *poll_list, int size)
{
    poll_handling_t *node = head;
    int i = 0;

    while (node != NULL && i < size) {
        poll_list[i].fd = node->poll_fd.fd;
        poll_list[i].events = POLLIN;
        poll_list[i].revents = 0;
        node = node->next;
        i++;
    }
    return poll_list;
}

void convert_poll_handling_reverse(poll_handling_t *head,
    struct pollfd *poll_list, int size)
{
    poll_handling_t *node = head;
    int i = 0;

    while (node != NULL && i < size) {
        node->poll_fd.fd = poll_list[i].fd;
        node->poll_fd.events = poll_list[i].events;
        node->poll_fd.revents = poll_list[i].revents;
        node = node->next;
        i++;
    }
}

/*
** EPITECH PROJECT, 2025
** poll_handling.h
** File description:
** poll_handling.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef POLL_HANDLING_H
    #define POLL_HANDLING_H

    #include <poll.h>
    #include "player.h"

typedef struct poll_handling_s {
    struct pollfd poll_fd;
    ai_stats_t *player;
    struct poll_handling_s *next;
} poll_handling_t;

int append_node_poll_handling(poll_handling_t **head,
    int fd, bool create_client);
struct pollfd *convert_poll_handling(poll_handling_t *head,
    struct pollfd *poll_list, int size);
void convert_poll_handling_reverse(poll_handling_t *head,
    struct pollfd *poll_list, int size);
void remove_node_poll_handling(poll_handling_t **head, int fd);

#endif //POLL_HANDLING_H

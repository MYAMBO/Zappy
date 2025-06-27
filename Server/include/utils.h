/*
** EPITECH PROJECT, 2025
** utils.h
** File description:
** utils.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef UTILS_H
    #define UTILS_H

    #include <stddef.h>
    #include "poll_handling.h"
    #include "struct.h"
    #include <string.h>

poll_handling_t *search_player_node(int id, server_t *server);
int array_len(char **arr);
int send_message_graphic(server_t *server, char *message);

#endif //UTILS_H

/*
** EPITECH PROJECT, 2025
** send_init_graphic.c
** File description:
** send_init_graphic.c
** created and edited by antoiix.
** All rights reserved
*/

#include "send_init_graphic.h"
#include <string.h>
#include <unistd.h>

#include "garbage.h"
#include "server.h"
#include "technical_protocol.h"

int send_graphic_init(server_t *server, poll_handling_t *node)
{
    (void)server;
    char *str = get_server_message("Welcome to Zappy !");

    (void) server;
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    return SUCCESS;
}

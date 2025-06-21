/*
** EPITECH PROJECT, 2025
** handle_connection.h
** File description:
** handle_connection.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef HANDLE_CONNECTION_H
    #define HANDLE_CONNECTION_H

    #include <stdio.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <bits/socket.h>
    #include "garbage.h"
    #include "logger.h"
    #include "server.h"
    #include "struct.h"

int handle_connection(server_t *server, pollfd_t poll);
int send_message_disconnect(poll_handling_t *node);

#endif //HANDLE_CONNECTION_H

/*
** EPITECH PROJECT, 2025
** server.h
** File description:
** server.h
** created and edited by antoiix.
** All rights reserved
*/



#ifndef SERVER_H
    #define SERVER_H

    #define FAILURE 84
    #define SUCCESS 0

    #define MAX_CLIENT 100

    #include "struct.h"
    #include "poll_handling.h"

typedef struct pollfd pollfd_t;

int *is_running(void);
int start_server(server_t *server);
int handle_event(server_t *server);
void init_density(server_t *server);
int init_server(server_t *server, long port);

#endif //SERVER_H

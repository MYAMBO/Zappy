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

#include "struct.h"
#include "poll_handling.h"

#define FAILURE 84
#define SUCCESS 0

#define MAX_CLIENT 100

int init_server(server_t *server, long port);
int start_server(server_t *server);
int handle_event(server_t* server);

#endif //SERVER_H

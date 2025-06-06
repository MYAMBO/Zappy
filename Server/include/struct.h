/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** struct.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef STRUCT_H
#define STRUCT_H

#include "poll_handling.h"

typedef struct server_s
{
    long port;
    int server_fd;
    poll_handling_t *poll_list;
    int poll_count;
} server_t;

#endif //STRUCT_H

/*
** EPITECH PROJECT, 2025
** unique_connection_id_getter.c
** File description:
** unique_connection_id_getter.c
** created and edited by antoiix.
** All rights reserved
*/

#include "unique_connection_id_getter.h"

int get_unique_connection_id(void)
{
    static int id = -1;

    id++;
    return id;
}

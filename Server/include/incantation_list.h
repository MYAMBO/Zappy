/*
** EPITECH PROJECT, 2025
** incantation_list.h
** File description:
** incantation_list.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef INCANTATION_LIST_H
    #define INCANTATION_LIST_H

    #include "struct.h"

int add_incantation(incantation_list_t **head, int incantation_nb, int tick_actual, int xy_lev[3]);
void pop_incantation(incantation_list_t **head);

#endif //INCANTATION_LIST_H

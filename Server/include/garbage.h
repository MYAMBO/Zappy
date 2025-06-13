/*
** EPITECH PROJECT, 2025
** garbage.h
** File description:
** garbage.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef GARBAGE_H
    #define GARBAGE_H

    #include "stdlib.h"

typedef struct garbage_s {
    void *data;
    struct garbage_s *next;
} garbage_t;

void free_garbage(void);
void *my_malloc(size_t size);

#endif //GARBAGE_H

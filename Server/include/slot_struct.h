/*
** EPITECH PROJECT, 2025
** slot_struct.h
** File description:
** slot_struct.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef SLOT_STRUCT_H
    #define SLOT_STRUCT_H

typedef struct slot_s {
    int id_slot;
    int id_user;
    int x;
    int y;
    int global_id;
    struct slot_s *next;
} slot_t;

typedef struct slot_table_s {
    char *name;
    int nb_slots;
    int slots_remaining;
    int id_slot_current;
    slot_t *slots;
} slot_table_t;

#endif //SLOT_STRUCT_H

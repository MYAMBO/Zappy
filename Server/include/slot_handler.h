/*
** EPITECH PROJECT, 2025
** slot_handler.h
** File description:
** slot_handler.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef SLOT_HANDLER_H
    #define SLOT_HANDLER_H

typedef struct slot_s {
    int id_slot;
    int id_user;
    struct slot_s *next;
} slot_t;

typedef struct slot_table_s {
    char *name;
    int nb_slots;
    int slots_remaining;
    int id_slot_current;
    slot_t *slots;
} slot_table_t;

int add_slot(slot_table_t *slot_table);
slot_table_t *create_slot_table(int nb_slots, char *name);
int connect_player(slot_table_t *slot_table, int id_user);
int disconnect_player(slot_table_t **slot_table, int id_user);

#endif //SLOT_HANDLER_H

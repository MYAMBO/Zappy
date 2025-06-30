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
    #include "struct.h"
    #include <time.h>
    #include "garbage.h"
    #include "server.h"
    #include "slot_struct.h"

int add_slot(slot_table_t *slot_table, int xy[2], int id_user, server_t *server);
slot_table_t *create_slot_table(int nb_slots, char *name, server_t *server);
int connect_player(slot_table_t *slot_table, ai_stats_t *user);
int disconnect_player(slot_table_t **slot_table, int id_user);
void remove_slot(slot_t **slot_table, int id_slot);

#endif //SLOT_HANDLER_H

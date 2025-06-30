/*
** EPITECH PROJECT, 2025
** send_slots_remaining.h
** File description:
** send_slots_remaining.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef SEND_SLOTS_REMAINING_H
    #define SEND_SLOTS_REMAINING_H

    #include <unistd.h>
    #include "egg_protocol.h"
    #include "player_connection_protocol.h"
    #include "poll_handling.h"
    #include "slot_struct.h"
    #include "struct.h"
    #include "utils.h"

int send_slot_remaining_mess(server_t *server, poll_handling_t *node,
    char **str, int i);
int remaining_massages_part_two(poll_handling_t *node,
    char *str, slot_t *slot, server_t *server);

#endif //SEND_SLOTS_REMAINING_H

/*
** EPITECH PROJECT, 2025
** send_slot_messages.h
** File description:
** send_slot_messages.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef SEND_SLOT_MESSAGES_H
    #define SEND_SLOT_MESSAGES_H

    #include <unistd.h>
    #include "command_exec_handler.h"
    #include "egg_protocol.h"
    #include "garbage.h"
    #include "player_connection_protocol.h"
    #include "send_init_graphic.h"
    #include "server.h"
    #include "slot_handler.h"
    #include "utils.h"

int send_slot_remaining(int *val, server_t *server,
    poll_handling_t *node, char **args);

#endif //SEND_SLOT_MESSAGES_H

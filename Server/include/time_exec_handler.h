/*
** EPITECH PROJECT, 2025
** time_exec_handler.h
** File description:
** time_exec_handler.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef TIME_EXEC_HANDLER_H
    #define TIME_EXEC_HANDLER_H

    #include <unistd.h>
    #include "actions_protocol.h"
    #include "command_exec_handler.h"
    #include "server.h"
    #include "slot_handler.h"
    #include "struct.h"
    #include "utils.h"

int time_exec_handler_exec(server_t *server);

#endif //TIME_EXEC_HANDLER_H

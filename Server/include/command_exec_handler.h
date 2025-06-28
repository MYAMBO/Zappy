/*
** EPITECH PROJECT, 2025
** command_exec_handler.h
** File description:
** command_exec_handler.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef COMMAND_EXEC_HANDLER_H
    #define COMMAND_EXEC_HANDLER_H

    #include "player.h"
    #include <string.h>
    #include "garbage.h"
    #include "server.h"
    #include "struct.h"

int add_command_exec(command_exec_t **head, char **args, int time_to_exec);
void command_exec_queue(poll_handling_t *node, int actual_tick);
int launch_command_exec(poll_handling_t *node, int actual_tick,
    server_t *server);

#endif //COMMAND_EXEC_HANDLER_H

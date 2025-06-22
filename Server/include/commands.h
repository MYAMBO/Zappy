/*
** EPITECH PROJECT, 2025
** commands.h
** File description:
** commands.h
** created and edited by antoiix.
** All rights reserved
*/

#ifndef COMMANDS_H
    #define COMMANDS_H

    #include <stdio.h>
    #include "struct.h"

int execute_command(const char *concat_command, server_t *server,
    poll_handling_t *node);
int quit_command(server_t *server, poll_handling_t *node, char **args);
int pin_command(server_t *server, poll_handling_t *node, char **args);
int forward_command(server_t *server, poll_handling_t *node, char **args);

static entry_t const commands_ai_list[] = {
    {"quit", quit_command},
    {"Forward", forward_command},
    {NULL, NULL}
};

static entry_t const commands_gui_list[] = {
    {"pin", pin_command},
    {NULL, NULL}
};

#endif //COMMANDS_H

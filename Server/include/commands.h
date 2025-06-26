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
int right_command(server_t *server, poll_handling_t *node, char **args);
int left_command(server_t *server, poll_handling_t *node, char **args);
int look_command(server_t *server, poll_handling_t *node, char **args);
int inventory_command(server_t *server, poll_handling_t *node, char **args);
int broadcast_command(server_t *server, poll_handling_t *node, char **args);
int eject_command(server_t *server, poll_handling_t *node, char **args);
int plv_command(server_t *server, poll_handling_t *node, char **args);
int ppo_command(server_t *server, poll_handling_t *node, char **args);
int msz_command(server_t *server, poll_handling_t *node, char **args);
int mct_command(server_t *server, poll_handling_t *node, char **args);
int bct_command(server_t *server, poll_handling_t *node, char **args);
int take_command(server_t *server, poll_handling_t *node, char **args);

static entry_t const commands_ai_list[] = {
    {"quit", quit_command},
    {"Forward", forward_command},
    {"Right", right_command},
    {"Left", left_command},
    {"Look", look_command},
    {"Inventory", inventory_command},
    {"Broadcast", broadcast_command},
    {"Eject", eject_command},
    {NULL, NULL}
};

static entry_t const commands_gui_list[] = {
    {"pin", pin_command},
    {"plv", plv_command},
    {"ppo", ppo_command},
    {"msz", msz_command},
    {"mct", mct_command},
    {"bct", bct_command},
    {NULL, NULL}
};

#endif //COMMANDS_H

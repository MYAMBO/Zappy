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
int sgt_command(server_t *server, poll_handling_t *node, char **args);
int tna_command(server_t *server, poll_handling_t *node, char **args);
int sst_command(server_t *server, poll_handling_t *node, char **args);
int take_command(server_t *server, poll_handling_t *node, char **args);
int drop_command(server_t *server, poll_handling_t *node, char **args);
int connect_nbr_command(server_t *server, poll_handling_t *node, char **args);

static entry_ai_t const commands_ai_list[] = {
    {"quit", quit_command, 0},
    {"Forward", forward_command, 7},
    {"Right", right_command, 7},
    {"Left", left_command, 7},
    {"Look", look_command, 7},
    {"Inventory", inventory_command, 1},
    {"Broadcast", broadcast_command, 7},
    {"Eject", eject_command, 7},
    {"Take", take_command, 7},
    {"Set", drop_command, 7},
    {"Connect_nbr", connect_nbr_command, 0},
    {NULL, NULL, 0}
};

static entry_gui_t const commands_gui_list[] = {
    {"pin", pin_command},
    {"plv", plv_command},
    {"ppo", ppo_command},
    {"msz", msz_command},
    {"mct", mct_command},
    {"bct", bct_command},
    {"sgt", sgt_command},
    {"sst", sst_command},
    {"tna", tna_command},
    {NULL, NULL}
};

#endif //COMMANDS_H

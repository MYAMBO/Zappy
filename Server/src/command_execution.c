/*
** EPITECH PROJECT, 2025
** command_execution.c
** File description:
** command_execution.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "commands.h"
#include "command_exec_handler.h"
#include "egg_protocol.h"
#include "garbage.h"
#include "handle_connection.h"
#include "logger.h"
#include "server.h"
#include "split_string.h"
#include "graphic_connect.h"
#include "player_connection_protocol.h"
#include "send_init_graphic.h"
#include "send_slot_messages.h"
#include "slot_handler.h"
#include "technical_protocol.h"
#include "utils.h"

int send_map_size_message(server_t *server,
    poll_handling_t *node)
{
    int j;
    char *str;

    j = snprintf(NULL, 0, "%d %d\n",
        server->map_width, server->map_height);
    str = my_malloc((j + 1) * sizeof(char));
    if (str == NULL)
        return FAILURE;
    sprintf(str, "%d %d\n",
        server->map_width, server->map_height);
    write(node->poll_fd.fd, str, j);
    my_free(str);
    node->player->connected = true;
    return SUCCESS;
}

int execute_commands_graphic(server_t *server, poll_handling_t *node,
    char **args)
{
    for (int i = 0; commands_gui_list[i].command != NULL; i++) {
        if (strcmp(args[0], commands_gui_list[i].command) != 0)
            continue;
        if (commands_gui_list[i].function(server, node, args) == FAILURE) {
            my_free_array(args);
            return FAILURE;
        }
        return SUCCESS;
    }
    write(node->poll_fd.fd, "suc\n", 4);
    return SUCCESS;
}

static int send_fork_message(char **args, poll_handling_t *node,
    server_t *server)
{
    char *str;

    if (strcmp(args[0], "Fork") == 0) {
        str = player_laying_egg(node->player);
        if (!str)
            return FAILURE;
        send_message_graphic(server, str);
        my_free(str);
    }
    return SUCCESS;
}

static int execute_command_loop(server_t *server,
    poll_handling_t *node, char **args)
{
    if (is_graphic_user(server, node))
        return execute_commands_graphic(server, node, args);
    for (int i = 0; commands_ai_list[i].command != NULL; i++) {
        if (strcmp(args[0], commands_ai_list[i].command) != 0)
            continue;
        if (send_fork_message(args, node, server) == FAILURE)
            return FAILURE;
        if (add_command_exec(&node->player->command_exec_list,
            args, commands_ai_list[i].time) == FAILURE)
            return FAILURE;
        return SUCCESS;
    }
    write(node->poll_fd.fd, "ko\n", 3);
    return SUCCESS;
}

static int execute_command_suite(poll_handling_t *node,
    char **args, server_t *server)
{
    int val = -1;

    if (!node->player->connected) {
        if (send_slot_remaining(&val, server, node, args) == FAILURE)
            return FAILURE;
        if (val != 0)
            write(node->poll_fd.fd, "ko\n", 3);
        my_free_array(args);
        return SUCCESS;
    }
    if (execute_command_loop(server, node, args) == FAILURE)
        return FAILURE;
    my_free_array(args);
    return SUCCESS;
}

int execute_command(const char *concat_command, server_t *server,
    poll_handling_t *node)
{
    char **args = split_string(concat_command, " \n");

    if (args == NULL)
        return FAILURE;
    if (args[0] == NULL) {
        write(node->poll_fd.fd, "ko\n", 3);
        my_free_array(args);
        return SUCCESS;
    }
    if (execute_command_suite(node, args, server) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

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
#include "garbage.h"
#include "handle_connection.h"
#include "logger.h"
#include "server.h"
#include "split_string.h"
#include "graphic_connect.h"

static int send_map_size_message(server_t *server,
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

static int send_slot_remaining_massages(server_t *server,
    poll_handling_t *node, int i)
{
    int j;
    char *str;

    j = snprintf(NULL, 0, "%d\n",
            server->team_names[i]->slots_remaining);
    str = my_malloc((j + 1) * sizeof(char));
    if (str == NULL)
        return FAILURE;
    sprintf(str, "%d\n", server->team_names[i]->slots_remaining);
    write(node->poll_fd.fd, str, j);
    my_free(str);
    if (send_map_size_message(server, node) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

static int send_slot_remaining(int *val, server_t *server,
    poll_handling_t *node, char **args)
{
    for (int i = 0; server->team_names[i] != NULL; i++) {
        if (strcmp(args[0], server->team_names[i]->name) != 0)
            continue;
        *val = connect_player(server->team_names[i], node->player->id);
        if (*val != 0)
            continue;
        node->player->team_name = my_malloc(sizeof(char) *
            (strlen(server->team_names[i]->name) + 1));
        if (node->player->team_name == NULL)
            return FAILURE;
        strcpy(node->player->team_name, server->team_names[i]->name);
        return send_slot_remaining_massages(server, node, i);
    }
    return SUCCESS;
}

// static int handle_disconnect(server_t *server,
//      poll_handling_t *node, int val)
// {
//     if (val != 0) {
//         if (send_message_disconnect(node) == FAILURE)
//             return FAILURE;
//         close(node->poll_fd.fd);
//         remove_node_poll_handling(&server->poll_list, node->poll_fd.fd);
//         server->poll_count--;
//     }
//     return SUCCESS;
// }
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

static int execute_command_loop(server_t *server,
    poll_handling_t *node, char **args)
{
    if (is_graphic_user(server, node))
        return execute_commands_graphic(server, node, args);
    for (int i = 0; commands_ai_list[i].command != NULL; i++) {
        if (strcmp(args[0], commands_ai_list[i].command) != 0)
            continue;
        if (commands_ai_list[i].function(server, node, args) == FAILURE) {
            my_free_array(args);
            return FAILURE;
        }
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

/*
** EPITECH PROJECT, 2025
** handle_event.c
** File description:
** handle_event.c
** created and edited by antoiix.
** All rights reserved
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include <arpa/inet.h>
#include <unistd.h>
#include "commands.h"
#include "garbage.h"
#include "handle_connection.h"
#include "logger.h"
#include "split_string.h"

static int send_message_disconnect(poll_handling_t *node)
{
    char *message = my_malloc(sizeof(char) * 1024);

    if (message == NULL)
        return FAILURE;
    sprintf(message, "Client disconnected with id : %d, "
        "local fd : %d", node->player->id, node->poll_fd.fd);
    logger_info(message, FILE_OUTPUT, true);
    my_free(message);
    return SUCCESS;
}

int handle_client_error(ssize_t bytes_read, server_t *server,
    poll_handling_t *node)
{
    if (bytes_read < 0) {
        perror("read failed");
        remove_node_poll_handling(&server->poll_list, node->poll_fd.fd);
        close(node->poll_fd.fd);
        server->poll_count--;
        return FAILURE;
    }
    if (bytes_read == 0) {
        if (send_message_disconnect(node) == FAILURE)
            return FAILURE;
        close(node->poll_fd.fd);
        remove_node_poll_handling(&server->poll_list, node->poll_fd.fd);
        server->poll_count--;
        return SUCCESS;
    }
    return 1;
}

int handle_command_concat(poll_handling_t *node, char *buffer)
{
    char *tmp_concat = my_malloc(sizeof(node->player->tmp_command)
            + sizeof(buffer) + 1);

    if (node->player->tmp_command == NULL) {
        node->player->tmp_command = my_malloc(sizeof(buffer));
        if (node->player->tmp_command == NULL)
            return FAILURE;
        strcpy(node->player->tmp_command, buffer);
    } else {
        if (tmp_concat == NULL)
            return FAILURE;
        strcpy(tmp_concat, node->player->tmp_command);
        strcat(tmp_concat, buffer);
        free(node->player->tmp_command);
        node->player->tmp_command = tmp_concat;
    }
    return SUCCESS;
}

int handle_merge_command(char **concat_command, char *buffer,
    poll_handling_t *node)
{
    char *command = strtok(buffer, "\n");

    if (node->player->tmp_command != NULL) {
        *concat_command = my_malloc(sizeof(node->player->tmp_command)
            + sizeof(buffer) + 1);
        if (*concat_command == NULL)
            return FAILURE;
        strcpy(*concat_command, node->player->tmp_command);
        if (command == NULL)
            return FAILURE;
        strcat(*concat_command, command);
        free(node->player->tmp_command);
        node->player->tmp_command = NULL;
    } else {
        *concat_command = my_malloc(sizeof(buffer) + 1);
        if (*concat_command == NULL)
            return FAILURE;
        strcpy(*concat_command, buffer);
    }
    return SUCCESS;
}

static int execute_command(char *concat_command, server_t *server,
    poll_handling_t *node)
{
    char **args = split_string(concat_command, " \n");

    if (args == NULL || args[0] == NULL)
        return FAILURE;
    for (int i = 0; commands_list[i].command != NULL; i++) {
        if (strcmp(args[0], commands_list[i].command) == 0 &&
            commands_list[i].function(server, node, args) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

static int handle_command_execution(char *buffer, server_t *server,
    poll_handling_t *node)
{
    char *concat_command = NULL;
    int handle_value = 0;

    if (strstr(buffer, "\n") == NULL) {
        handle_value = handle_command_concat(node, buffer);
        if (handle_value == FAILURE)
            return FAILURE;
        return SUCCESS;
    }
    if (handle_merge_command(&concat_command, buffer, node) == FAILURE)
        return FAILURE;
    if (execute_command(concat_command, server, node) == FAILURE)
        return FAILURE;
    return 1;
}

int handle_command(server_t *server, poll_handling_t *node)
{
    char buffer[1024] = {0};
    ssize_t bytes_read = 0;
    int handle_value = 0;

    if (!(node->poll_fd.revents & POLLIN))
        return SUCCESS;
    bytes_read = read(node->poll_fd.fd, buffer,
        sizeof(buffer) - 1);
    handle_value = handle_client_error(bytes_read, server, node);
    if (handle_value != 1)
        return handle_value;
    handle_value = handle_command_execution(buffer, server, node);
    if (handle_value != 1)
        return handle_value;
    return SUCCESS;
}

int handle_event(server_t *server)
{
    int val_connection;
    poll_handling_t *next = NULL;

    for (poll_handling_t *node = server->poll_list;
        node != NULL; node = next) {
        next = node->next;
        val_connection = handle_connection(server, node->poll_fd);
        if (val_connection == FAILURE)
            return FAILURE;
        if (val_connection == 1)
            continue;
        val_connection = handle_command(server, node);
        if (val_connection == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

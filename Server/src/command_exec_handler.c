/*
** EPITECH PROJECT, 2025
** command_exec_handler.c
** File description:
** command_exec_handler.c
** created and edited by antoiix.
** All rights reserved
*/

#include "command_exec_handler.h"

#include "commands.h"

command_exec_t *init_command_exec_handler(char **args, int time_to_exec)
{
    command_exec_t *tmp = my_malloc(sizeof(command_exec_t));
    int i;
    char **args_copy;

    for (i = 0; args[i] != NULL; i++);
    args_copy = my_malloc(sizeof(char *) * (i + 1));
    if (tmp == NULL || args_copy == NULL)
        return NULL;
    for (i = 0; args[i] != NULL; i++) {
        args_copy[i] = my_malloc(strlen(args[i]) + 1);
        if (args_copy[i] == NULL)
            return NULL;
        strcpy(args_copy[i], args[i]);
    }
    tmp->args = args_copy;
    tmp->time_to_exec = time_to_exec;
    tmp->tick_launch = -1;
    tmp->next = NULL;
    return tmp;
}

int add_command_exec(command_exec_t **head, char **args, int time_to_exec)
{
    command_exec_t *tmp = init_command_exec_handler(args, time_to_exec);
    command_exec_t *tmp2;

    if (tmp == NULL)
        return FAILURE;
    if (*head == NULL) {
        *head = tmp;
        return SUCCESS;
    }
    for (tmp2 = *head; tmp2->next != NULL; tmp2 = tmp2->next);
    tmp2->next = tmp;
    return SUCCESS;
}

void pop_command_exec(command_exec_t **head)
{
    command_exec_t *tmp = *head;

    if (tmp == NULL)
        return;
    *head = tmp->next;
    my_free(tmp->args);
    my_free(tmp);
}

void command_exec_queue(poll_handling_t *node, int actual_tick)
{
    command_exec_t *tmp;
    command_exec_t *next;

    if (!node || !node->player || !node->player->command_exec_list)
        return;
    tmp = node->player->command_exec_list;
    while (node->player->in_incantation != -1 && strcmp(tmp->args[0],
        "Incantation") == 0 && tmp->time_to_exec == 300 && tmp) {
        next = tmp->next;
        pop_command_exec(&node->player->command_exec_list);
        tmp = next;
    }
    if (tmp == NULL)
        return;
    if (tmp->tick_launch == -1)
        tmp->tick_launch = actual_tick + tmp->time_to_exec * 1000;
    if (node->player->in_incantation != -1) {
        tmp->tick_launch++;
    }
}

int launch_command_exec(poll_handling_t *node, int actual_tick,
    server_t *server)
{
    if (!node || !node->player || !node->player->command_exec_list)
        return SUCCESS;
    if (actual_tick < node->player->command_exec_list->tick_launch)
        return SUCCESS;
    for (int i = 0; commands_ai_list[i].command != NULL; i++) {
        if (strcmp(node->player->command_exec_list->args[0],
            commands_ai_list[i].command) != 0)
            continue;
        if (commands_ai_list[i].function(server, node,
            node->player->command_exec_list->args) == FAILURE)
            return FAILURE;
        break;
    }
    pop_command_exec(&node->player->command_exec_list);
    return SUCCESS;
}

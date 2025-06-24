/*
** EPITECH PROJECT, 2025
** command_inventory.c
** File description:
** command_inventory.c
** created and edited by antoiix.
** All rights reserved
*/

#include <unistd.h>
#include "commands.h"
#include "inventory_communication.h"
#include "utils.h"

int inventory_command(server_t *server, poll_handling_t *node, char **args)
{
    (void)server;
    if (array_len(args) != 1) {
        write(node->poll_fd.fd, "ko\n", 3);
        return SUCCESS;
    }
    char *str = inventory_communication(node->player);
    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    return SUCCESS;
}

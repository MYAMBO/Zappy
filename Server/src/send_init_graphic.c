/*
** EPITECH PROJECT, 2025
** send_init_graphic.c
** File description:
** send_init_graphic.c
** created and edited by antoiix.
** All rights reserved
*/

#include "send_init_graphic.h"
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "egg_protocol.h"
#include "garbage.h"
#include "server.h"
#include "technical_protocol.h"

int launch_eggs_display(poll_handling_t *node, slot_table_t *table)
{
    slot_t *slot = table->slots;
    char *str = NULL;

    for (; slot; slot = slot->next)
    {
        str = egg_wad_laid(slot);
        if (!str)
            return FAILURE;
        write(node->player->fd, str, strlen(str));
        my_free(str);
    }
    return SUCCESS;
}

int send_graphic_suite(server_t *server, poll_handling_t *node)
{
    for (int i = 0; server->team_names[i] != NULL; i++)
    {
        if (strcmp(server->team_names[i]->name, "GRAPHIC") == 0)
            continue;
        if (launch_eggs_display(node,
            server->team_names[i]) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int send_graphic_init(server_t *server, poll_handling_t *node)
{
    char *str = get_server_message("Welcome to Zappy !");
    char *args[] = {"command", NULL};

    if (str == NULL)
        return FAILURE;
    write(node->poll_fd.fd, str, strlen(str));
    my_free(str);
    if (msz_command(server, node, args) == FAILURE)
        return FAILURE;
    if (sgt_command(server, node, args) == FAILURE)
        return FAILURE;
    if (mct_command(server, node, args) == FAILURE)
        return FAILURE;
    if (tna_command(server, node, args) == FAILURE)
        return FAILURE;
    if (send_graphic_suite(server, node) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

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
#include "player_connection_protocol.h"
#include "server.h"
#include "technical_protocol.h"
#include "utils.h"

int launch_eggs_display(poll_handling_t *node, slot_table_t *table)
{
    slot_t *slot = table->slots;
    char *str = NULL;

    for (; slot; slot = slot->next) {
        str = egg_wad_laid(slot);
        if (!str)
            return FAILURE;
        write(node->player->fd, str, strlen(str));
        my_free(str);
    }
    return SUCCESS;
}

static int send_pnw(server_t *server, poll_handling_t *node)
{
    char *str = player_new_connection(node->player);

    if (str == NULL)
        return FAILURE;
    if (send_message_graphic(server, str) == FAILURE)
        return FAILURE;
    my_free(str);
    return SUCCESS;
}

static poll_handling_t *get_node(server_t *server)
{
    poll_handling_t *tmp;

    for (tmp = server->poll_list; tmp; tmp = tmp->next) {
        if (tmp->player && strcmp(tmp->player->team_name, "GRAPHIC") == 0)
            break;
    }
    return tmp;
}

int send_info_user(server_t *server, poll_handling_t *node)
{
    char **args = my_malloc(sizeof(char *) * 3);
    int a;
    poll_handling_t *tmp = get_node(server);

    if (args == NULL)
        return FAILURE;
    if (tmp == NULL)
        return SUCCESS;
    args[0] = "command";
    args[1] = NULL;
    args[2] = NULL;
    a = snprintf(NULL, 0, "#%d", node->player->id);
    args[1] = my_malloc(a + 1);
    sprintf(args[1], "#%d", node->player->id);
    if (pin_command(server, tmp, args) == FAILURE ||
        plv_command(server, tmp, args) == FAILURE ||
        ppo_command(server, tmp, args) == FAILURE)
        return FAILURE;
    my_free_array(args);
    return SUCCESS;
}

int send_player_info(server_t *server, poll_handling_t *node, char **args)
{
    int a;

    for (poll_handling_t *tmp = server->poll_list; tmp; tmp = tmp->next) {
        if (!tmp->player || strcmp(tmp->player->team_name, "GRAPHIC") == 0 ||
            !tmp->player->connected)
            continue;
        my_free(args[1]);
        a = snprintf(NULL, 0, "#%d", tmp->player->id);
        args[1] = my_malloc(a + 1);
        sprintf(args[1], "#%d", tmp->player->id);
        if (send_pnw(server, tmp) == FAILURE ||
            pin_command(server, node, args) == FAILURE ||
            plv_command(server, node, args) == FAILURE ||
            ppo_command(server, node, args) == FAILURE)
            return FAILURE;
    }
    my_free_array(args);
    return SUCCESS;
}

int send_graphic_suite(server_t *server, poll_handling_t *node)
{
    char **args = my_malloc(sizeof(char *) * 3);

    if (args == NULL)
        return FAILURE;
    args[0] = "command";
    args[1] = NULL;
    args[2] = NULL;
    for (int i = 0; server->team_names[i] != NULL; i++) {
        if (strcmp(server->team_names[i]->name, "GRAPHIC") == 0)
            continue;
        if (launch_eggs_display(node,
            server->team_names[i]) == FAILURE)
            return FAILURE;
    }
    if (send_player_info(server, node, args) == FAILURE)
        return FAILURE;
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

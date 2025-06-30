/*
** EPITECH PROJECT, 2025
** handle_fork_communication.c
** File description:
** handle_fork_communication.c
** created and edited by antoiix.
** All rights reserved
*/

#include "handle_fork_communication.h"
#include "egg_protocol.h"
#include "utils.h"

char *handle_fork_action(ai_stats_t *player, server_t *server)
{
    char *str;
    slot_t *slot;

    for (int i = 0; server->team_names[i] != NULL; i++) {
        if (strcmp(server->team_names[i]->name, player->team_name) == 0) {
            if (add_slot(server->team_names[i], (int[2]){player->x, player->y}, player->id, server) == FAILURE)
                return NULL;
            for (slot = server->team_names[i]->slots; slot->next; slot = slot->next);
            str = egg_wad_laid(slot);
            if (!str)
                return NULL;
            if (send_message_graphic(server, str) == FAILURE)
                return NULL;
            return "ok\n";
        }
    }
    return "ok\n";
}

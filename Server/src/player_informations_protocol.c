//
// Created by pierre on 6/10/25.
//

#include "player_informations_protocol.h"


char *get_teams_name(server_t *server)
{
    int total_len = 0;
    char *result = NULL;
    char *buffer = NULL;

    for (int i = 0; server->team_names[i] != NULL; i++)
        total_len += snprintf(NULL, 0, "tna %s\n", server->team_names[i]);
    result = my_malloc(total_len + 1);
    if (!result)
        return NULL;
    buffer = my_malloc(total_len + 1);
    if (!buffer)
        return NULL;
    result[0] = '\0';
    for (int i = 0; server->team_names[i]; i++) {
        snprintf(buffer, total_len + 1, "tna %s\n", server->team_names[i]);
        strcat(result, buffer);
    }

    //my_free needed here for buffer

    return result;
}
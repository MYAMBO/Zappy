/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** map_protocol
*/


#ifndef ZAPPY_MAP_PROTOCOL_H
    #define ZAPPY_MAP_PROTOCOL_H

    #include "stdio.h"
    #include "string.h"
    #include "server.h"
    #include "garbage.h"

char *get_map_size(server_t *server);
char *get_tile_content(map_t *map, int x, int y);
char *get_map_content(map_t *map);



#endif //ZAPPY_MAP_PROTOCOL_H

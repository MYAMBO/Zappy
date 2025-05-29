/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.hpp
*/

#ifndef ZAPPY_PLAYER_HPP
#define ZAPPY_PLAYER_HPP

#include "../include/AEntity.hpp"

namespace Gui {
    class Player : public AEntity {
        public:
            Player(Vector3 position, float scale, CLITERAL(Color) color);
            ~Player();
    };
};

#endif //ZAPPY_PLAYER_HPP

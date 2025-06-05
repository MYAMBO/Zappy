/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.hpp
*/

#ifndef ZAPPY_PLAYER_HPP
    #define ZAPPY_PLAYER_HPP

    #include <tuple>
    #include "AEntity.hpp"

enum orientation {
    North,
    Est,
    South,
    West
};

namespace gui {
    class Player : public AEntity {
        public:
            Player(Vector3 position, float scale, CLITERAL(Color) color);
            ~Player();

            void Left();
            void Right();
            void forward();
        private:
            orientation _direction;
    };
};

#endif //ZAPPY_PLAYER_HPP

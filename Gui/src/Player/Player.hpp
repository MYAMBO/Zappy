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

enum Orientation {
    North,
    Est,
    South,
    West
};

namespace gui {
    class Player : public AEntity {
        public:
            Player(int id, std::pair<int, int> position, Orientation orientation, int level, const std::string& team);

            ~Player();

            int _id;
            Orientation _orientation;
            int _level{};
            std::string _team;
    };
}

#endif //ZAPPY_PLAYER_HPP

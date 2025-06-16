/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Thystame
*/

#ifndef ZAPPY_THYSTAME_HPP
    #define ZAPPY_THYSTAME_HPP

    #include "AItem.hpp"

namespace gui {
    class Thystame : public AItem {
        public:
            Thystame(Vector3 position, float scale);
            ~Thystame();

            std::string getType() override;
    };
}

#endif
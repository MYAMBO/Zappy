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
            Thystame(std::pair<int, int> position, float scale, std::shared_ptr<Model> model);
            ~Thystame();

            std::string getType() override;
    };
}

#endif
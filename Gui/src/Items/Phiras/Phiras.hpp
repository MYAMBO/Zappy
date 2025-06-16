/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Phiras
*/

#ifndef ZAPPY_PHIRAS_HPP
    #define ZAPPY_PHIRAS_HPP

    #include "AItem.hpp"

namespace gui {
    class Phiras : public AItem {
        public:
            Phiras(std::pair<int, int> position, float scale);
            ~Phiras();

            std::string getType() override;
    };
}

#endif
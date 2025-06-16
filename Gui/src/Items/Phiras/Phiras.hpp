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
            Phiras(Vector3 position, float scale, Color color);
            ~Phiras();

            std::string getType() override;
    };
}

#endif
/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Linemate
*/

#ifndef ZAPPY_LINEMATE_HPP
    #define ZAPPY_LINEMATE_HPP

    #include "AItem.hpp"

namespace gui {
    class Linemate : public AItem {
        public:
            Linemate(Vector3 position, float scale);
            ~Linemate();

            std::string getType() override;
    };
}

#endif
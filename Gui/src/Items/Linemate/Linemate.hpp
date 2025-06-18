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
            Linemate(std::pair<int, int> position, float scale, std::shared_ptr<Model> model);
            ~Linemate();

            std::string getType() override;
    };
}

#endif
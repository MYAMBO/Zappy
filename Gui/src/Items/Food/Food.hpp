/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Food
*/

#ifndef ZAPPY_FOOD_HPP
    #define ZAPPY_FOOD_HPP

    #include "AItem.hpp"

namespace gui {
    class Food : public AItem {
        public:
            Food(Vector3 position, float scale);
            ~Food();

            std::string getType() override;
    };
}

#endif
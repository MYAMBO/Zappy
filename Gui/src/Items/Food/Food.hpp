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
            Food(std::pair<int, int> position, float scale, std::shared_ptr<Model> model);
            ~Food();

            std::string getType() override;
    };
}

#endif
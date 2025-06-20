/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Deraumere
*/

#ifndef ZAPPY_DERAUMERE_HPP
    #define ZAPPY_DERAUMERE_HPP

    #include "AItem.hpp"

namespace gui {
    class Deraumere : public AItem {
        public:
            Deraumere(std::pair<int, int> position, float scale, std::shared_ptr<Model> model);
            ~Deraumere();

            std::string getType() override;
    };
}

#endif
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
            Deraumere(Vector3 position, float scale);
            ~Deraumere();

            std::string getType() override;
    };
}

#endif
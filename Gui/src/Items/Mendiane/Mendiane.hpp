/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Mendiane
*/

#ifndef ZAPPY_MENDIANE_HPP
    #define ZAPPY_MENDIANE_HPP

    #include "AItem.hpp"

namespace gui {
    class Mendiane : public AItem {
        public:
            Mendiane(Vector3 position, float scale, Color color);
            ~Mendiane();

            std::string getType() override;
    };
}

#endif
/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Sibur
*/

#ifndef ZAPPY_SIBUR_HPP
    #define ZAPPY_SIBUR_HPP

    #include "AItem.hpp"

namespace gui {
    class Sibur : public AItem {
        public:
            Sibur(Vector3 position, float scale, Color color);
            ~Sibur();

            std::string getType() override;
    };
}

#endif
/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Kayu.hpp
*/

#ifndef ZAPPY_KAYU_HPP
#define ZAPPY_KAYU_HPP

#include "../include/AEntity.hpp"

namespace Gui {
    class Kayu : public AEntity {
        public:
            Kayu(Vector3 position, float scale, CLITERAL(Color) color);
            ~Kayu();
    };
};

#endif //ZAPPY_KAYU_HPP

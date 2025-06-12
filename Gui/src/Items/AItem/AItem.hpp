/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AItem.hpp
*/

#ifndef ZAPPY_AITEM_HPP
    #define ZAPPY_AITEM_HPP

    #include "AEntity.hpp"

namespace gui {
    class AItem : public AEntity {
        public:
            AItem(Vector3 position, float scale, Color color);
            ~AItem();
    };
};

#endif

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** TileInventory.hpp
*/

#ifndef ZAPPY_TILEINVENTORY_HPP
#define ZAPPY_TILEINVENTORY_HPP

#include "AInventory.hpp"



namespace gui::ui {
    class TileInventory : public AInventory {
    public:
        void draw() override;

        void drawTileInformation();

    private:
    };
}


#endif //ZAPPY_TILEINVENTORY_HPP

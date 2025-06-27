/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** TileInventory.cpp
*/

#include "TileInventory.hpp"

void gui::ui::TileInventory::draw()
{
    AInventory::drawBackground();
    drawTileInformation();
    AInventory::drawItems();
}

void gui::ui::TileInventory::drawTileInformation()
{
    std::string string = "Tile : " + std::to_string(_coord.first) + "/" + std::to_string(_coord.second);
    DrawText(string.c_str(), _tileInventory.x + 10, _tileInventory.y + 10, _fontSize, BLACK);
}

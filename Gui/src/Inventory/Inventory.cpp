/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Inventory
*/

#include "Inventory.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::ui::Inventory::Inventory(int screenWidth, int screenHeight)
    : _fontSize(20), _bounds({0, static_cast<float>(screenHeight) * 0.89f, static_cast<float>(screenWidth), static_cast<float>(screenHeight) / 5.0f})
{
}

gui::ui::Inventory::~Inventory()
{
}


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/


void gui::ui::Inventory::draw()
{
    DrawRectangleRec(_bounds, {255, 255, 255, 50});
    DrawRectangleLinesEx(_bounds, 2, BLACK);
    DrawText("Inventory", _bounds.x + 10, _bounds.y + 10, _fontSize, BLACK);
}


/************************************************************
**                   >>>>   SETTERS   <<<<                 **
************************************************************/


void gui::ui::Inventory::setBounds(Rectangle bounds)
{
    _bounds = bounds;
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


Rectangle gui::ui::Inventory::getBounds() const
{
    return _bounds;
}
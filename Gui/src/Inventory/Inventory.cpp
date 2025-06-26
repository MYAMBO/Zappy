/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Inventory
*/

#include "Logger.hpp"
#include "Inventory.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::ui::Inventory::Inventory(int screenWidth, int screenHeight)
    : _fontSize(30), _bounds({0, static_cast<float>(screenHeight) * 0.8f, static_cast<float>(screenWidth), static_cast<float>(screenHeight) / 5.0f})
{
    _items = {
        {"Food", {10, BROWN}},
        {"Linemate", {0, YELLOW}},
        {"Deraumere", {0, GREEN}},
        {"Sibur", {0, RED}},
        {"Mendiane", {0, WHITE}},
        {"Phiras", {0, BLUE}},
        {"Thystame", {0, PURPLE}}
    };
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

    float itemWidth = _bounds.width / static_cast<float>(_items.size());
    int index = 0;
    
    for (const auto& item : _items) {
        std::string text = item.first + ": " + std::to_string(item.second.first);
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), _fontSize, 1);
        float textX = _bounds.x + index * itemWidth + (itemWidth - textSize.x) / 2;
        float textY = _bounds.y + (_bounds.height - textSize.y) / 2;
        DrawText(text.c_str(), static_cast<int>(textX), static_cast<int>(textY), _fontSize, item.second.second);
        index++;
    }
}

/************************************************************
**                   >>>>   SETTERS   <<<<                 **
************************************************************/


void gui::ui::Inventory::setBounds(Rectangle bounds)
{
    _bounds = bounds;
}

void gui::ui::Inventory::setInventoryItem(const std::string& item, int quantity)
{
    if (_items.find(item) != _items.end()) {
        _items[item].first = quantity;
    }
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


Rectangle gui::ui::Inventory::getBounds() const
{
    return _bounds;
}

int gui::ui::Inventory::getInventoryItem(const std::string& item) const
{
    auto it = _items.find(item);

    if (it != _items.end()) {
        return it->second.first;
    }
    return 0;
}
/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PlayerInventory.cpp
*/

#include "PlayerInventory.hpp"
#include "Type.hpp"

void gui::ui::PlayerInventory::draw()
{
    AInventory::drawBackground();
    drawPlayerInformation();
    AInventory::drawItems();
}

void gui::ui::PlayerInventory::drawPlayerInformation()
{
    DrawText("Inventory", static_cast<int>(_bounds.x) + 10, static_cast<int>(_bounds.y) + 10, _fontSize, BLACK);

    std::string text;
    if (_team.size() > 5)
        text = _team.substr(0, 5) + "... : ";
    else
        text = _team + " : ";
    DrawText(("Team name: " + text).c_str(), SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT * 0.8f + 10, 30, _color);
    DrawText(("Player ID: " + std::to_string(_id)).c_str(), SCREEN_WIDTH / 2.8, SCREEN_HEIGHT * 0.8f + 10, 30, _color);
    int falseId = _id;
    int counter = 0;
    if (falseId > static_cast<int>(_playersNames.size())) {
        while (falseId >= static_cast<int>(_playersNames.size())) {
            counter++;
            falseId -= static_cast<int>(_playersNames.size());
        }
    }
    if (counter == 0)
        DrawText(("Player name: " + _playersNames[falseId]).c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.8f + 10, 30, _color);
    else
        DrawText(("Player name: " + _playersNames[falseId] + " " + std::to_string(counter)).c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.8f + 10, 30, _color);
    DrawText(("Level: " + std::to_string(_level)).c_str(), SCREEN_WIDTH / 1.2, SCREEN_HEIGHT * 0.8f + 10, 30, _color);
}

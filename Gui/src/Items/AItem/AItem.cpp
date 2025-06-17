/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AItem.cpp
*/

#include "AItem.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::AItem::AItem(std::pair<int, int> position, float scale, Color color)
    : AEntity({(float)position.first, 0.05, (float)position.second}, scale, color)
{
    float value1 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.8f - 0.4f;
    float value2 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.8f - 0.4f;

    Vector3 new_pos = {(float)position.first + value1, 0.55, (float)position.second + value2};

    setPosition(new_pos);
}

gui::AItem::~AItem() = default;
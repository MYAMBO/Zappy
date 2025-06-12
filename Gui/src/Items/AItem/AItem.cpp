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


gui::AItem::AItem(Vector3 position, float scale, Color color)
    : AEntity(position, scale, color)
{
    float value1 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.8f - 0.4f;
    float value2 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.8f - 0.4f;

    Vector3 new_pos = {position.x + value1, position.y, position.z + value2};

    AEntity::setPosition(new_pos);
}

gui::AItem::~AItem() = default;
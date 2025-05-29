/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Kayu.cpp
*/

#include "../include/Kayu.hpp"

Gui::Kayu::Kayu( Vector3 position, float scale, CLITERAL(Color) color) : AEntity("Kayu", position, scale, color)
{
    float value1 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.8f - 0.4f;
    float value2 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.8f - 0.4f;

    Vector3 new_pos = {position.x + value1, position.y, position.z + value2};

    AEntity::setPosition(new_pos);
}

Gui::Kayu::~Kayu() = default;

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Kayu.cpp
*/

#include "Kayu.hpp"

gui::Kayu::Kayu( Vector3 position, float scale, CLITERAL(Color) color) : AEntity("Kayu", position, scale, color)
{
    float value1 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.9f - 0.45f;
    float value2 = ((float)GetRandomValue(0, 10000) / 10000.0f) * 0.9f - 0.45f;

    Vector3 new_pos = {position.x + value1, position.y, position.z + value2};

    AEntity::setPosition(new_pos);
}

gui::Kayu::~Kayu() = default;

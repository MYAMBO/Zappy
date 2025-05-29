/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.cpp
*/

#include "../include/Player.hpp"

Gui::Player::Player( Vector3 position, float scale, CLITERAL(Color) color) : AEntity("Player", position, scale, color)
{
}

Gui::Player::~Player() = default;

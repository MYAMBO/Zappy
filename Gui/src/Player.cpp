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

void Gui::Player::Left()
{
    switch (this->_direction) {
        case North:
            this->_direction = West;
            break;
        case Est:
            this->_direction = North;
            break;
        case South:
            this->_direction = Est;
            break;
        case West:
            this->_direction = South;
            break;
    }
}

void Gui::Player::Right() {
    switch (this->_direction) {
        case North:
            this->_direction = Est;
            break;
        case Est:
            this->_direction = South;
            break;
        case South:
            this->_direction = West;
            break;
        case West:
            this->_direction = North;
            break;
    }
}

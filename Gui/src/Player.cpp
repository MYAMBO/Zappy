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

void Gui::Player::forward()
{
    float x = this->_position.x;
    float y = this->_position.y;
    float z = this->_position.z;

    switch (this->_direction) {
        case North:
            this->_position = {x, y, z + 1};
            break;
        case Est:
            this->_position = {x - 1, y, z};
            break;
        case South:
            this->_position = {x, y, z - 1};
            break;
        case West:
            this->_position = {x + 1, y, z};
            break;
    }
}

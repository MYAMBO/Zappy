/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.cpp
*/

#include "Player.hpp"

gui::Player::Player(int id, std::pair<int, int> position, Orientation orientation, int level, const std::string& team): AEntity("Player", {(float)position.first, 0, (float)position.second}, 1, WHITE), _id(id), _orientation(orientation), _level(level)
{
}

gui::Player::~Player() = default;

int gui::Player::getId() const
{
    return this->_id;
}

int gui::Player::getLevel() const
{
    return this->_level;
}

Orientation gui::Player::getOrientation() const
{
    return this->_orientation;
}

std::string gui::Player::getTeam() const
{
    return  this->_team;
}

void gui::Player::setLevel(int level)
{
    this->_level = level;
}

void gui::Player::setOrientation(Orientation orientation)
{
    this->_orientation = orientation;
}

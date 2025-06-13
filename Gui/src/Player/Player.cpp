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

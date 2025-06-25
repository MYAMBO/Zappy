/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"

#include <raymath.h>

gui::Egg::Egg(int id, std::pair<int, int> position, std::shared_ptr<Model> model)
    : AEntity({(float)position.first, 0.5f, (float)position.second}, 0.7f, WHITE), _id(id)
{
    _model = model;
    _model->transform = MatrixScale(_scale, _scale, _scale);
}

gui::Egg::~Egg() = default;

void gui::Egg::draw()
{
    DrawModel(*_model, _position, _scale, _color);
}

bool gui::Egg::crackEgg(std::pair<int, int> position)
{
    if (_position.x == (float)position.first && _position.z == (float)position.second)
        return true;
    return false;
}
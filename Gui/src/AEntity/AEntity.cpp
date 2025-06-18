/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AEntity
*/

#include "AEntity.hpp"

#include "Logger.hpp"
gui::AEntity::AEntity(Vector3 position, float scale, Color color) : _color(color), _position(position), _scale(scale)
{
}

gui::AEntity::~AEntity()
{
}

Color gui::AEntity::getColor()
{
    return _color;
}

std::shared_ptr<Model> gui::AEntity::getModel()
{
    return _model;
}

Vector3 gui::AEntity::getPosition()
{
    return _position;
}

float gui::AEntity::getScale()
{
    return _scale;
}

void gui::AEntity::setColor(Color color)
{
    _color = color;
}

void gui::AEntity::setModel(std::shared_ptr<Model> model)
{
    _model = model;
}

void gui::AEntity::setPosition(Vector3 position)
{
    _position = position;
}

void gui::AEntity::setScale(float scale)
{
    _scale = scale;
}

std::string gui::AEntity::getType()
{
    return "AEntity";
}
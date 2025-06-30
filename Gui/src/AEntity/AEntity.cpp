/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AEntity
*/

#include "Logger.hpp"
#include "AEntity.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::AEntity::AEntity(Vector3 position, float scale, Color color)
    : _color(color), _position(position), _scale(scale)
{
}

gui::AEntity::~AEntity()
{
}


/************************************************************
**                   >>>>   SETTERS   <<<<                 **
************************************************************/


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

void gui::AEntity::setRotationY(float rotationY)
{
    _rotationY = rotationY;
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


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

std::string gui::AEntity::getType()
{
    return "AEntity";
}

float gui::AEntity::getRotationY()
{
    return _rotationY;
}

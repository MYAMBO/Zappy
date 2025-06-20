/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Phiras
*/

#include "Phiras.hpp"

#include <raymath.h>
#include <utility>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Phiras::Phiras(std::pair<int, int> position, float scale, std::shared_ptr<Model> model)
    : AItem(position, scale, BLUE)
{
    _rotationY = ((float)rand() / RAND_MAX) * 360.0f;
    _model = std::move(model);
    _model->transform = MatrixScale(scale, scale, scale);
}

gui::Phiras::~Phiras()
{
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


std::string gui::Phiras::getType()
{
    return "Phiras";
}
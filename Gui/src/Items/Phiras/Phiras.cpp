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
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = std::move(model);

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model->transform = MatrixMultiply(scaleMatrix, rotationMatrix);
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
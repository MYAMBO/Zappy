/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Linemate
*/

#include "Linemate.hpp"

#include <raymath.h>
#include <utility>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Linemate::Linemate(std::pair<int, int> position, float scale, std::shared_ptr<Model> model)
    : AItem(position, scale, WHITE)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = std::move(model);

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model->transform = MatrixMultiply(scaleMatrix, rotationMatrix);
}

gui::Linemate::~Linemate()
{
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


std::string gui::Linemate::getType()
{
    return "Linemate";
}
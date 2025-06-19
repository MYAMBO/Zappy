/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Sibur
*/

#include "Sibur.hpp"

#include <raymath.h>
#include <utility>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Sibur::Sibur(std::pair<int, int> position, float scale, std::shared_ptr<Model> model)
    : AItem(position, scale, WHITE)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = std::move(model);

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model->transform = MatrixMultiply(scaleMatrix, rotationMatrix);
}

gui::Sibur::~Sibur()
{
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


std::string gui::Sibur::getType()
{
    return "Sibur";
}
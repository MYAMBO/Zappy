/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Mendiane
*/

#include "Mendiane.hpp"

#include <raymath.h>
#include <utility>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Mendiane::Mendiane(std::pair<int, int> position, float scale, std::shared_ptr<Model> model)
    : AItem(position, scale, WHITE)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = std::move(model);

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model->transform = MatrixMultiply(scaleMatrix, rotationMatrix);
}

gui::Mendiane::~Mendiane()
{
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


std::string gui::Mendiane::getType()
{
    return "Mendiane";
}
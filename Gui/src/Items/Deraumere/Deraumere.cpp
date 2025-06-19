/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Deraumere
*/

#include "Deraumere.hpp"

#include <raymath.h>
#include <utility>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Deraumere::Deraumere(std::pair<int, int> position, float scale, std::shared_ptr<Model> model)
    : AItem(position, scale, WHITE)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    this->_model = std::move(model);

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);

    this->_model->transform = MatrixMultiply(scaleMatrix, rotationMatrix);
}

gui::Deraumere::~Deraumere()
{
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


std::string gui::Deraumere::getType()
{
    return "Deraumere";
}
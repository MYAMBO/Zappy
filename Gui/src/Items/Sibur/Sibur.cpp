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
    _rotationY = ((float)rand() / RAND_MAX) * 360.0f;
    _model = std::move(model);
    _model->transform = MatrixScale(scale, scale, scale);
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
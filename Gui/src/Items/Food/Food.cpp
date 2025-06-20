/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Food
*/

#include "Food.hpp"
#include "Logger.hpp"

#include <utility>
#include <raymath.h>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Food::Food(std::pair<int, int> position, float scale, std::shared_ptr<Model> model)
    : AItem(position, scale, WHITE)
{
    _rotationY = ((float)rand() / RAND_MAX) * 360.0f;
    _model = std::move(model);
    _model->transform = MatrixScale(scale, scale, scale);
}


gui::Food::~Food()
{
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


std::string gui::Food::getType()
{
    return "Food";
}
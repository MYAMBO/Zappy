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
    _rotationY = ((float)rand() / RAND_MAX) * 360.0f;
    this->_model = std::move(model);
    this->_model->transform = MatrixScale(scale, scale, scale);
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
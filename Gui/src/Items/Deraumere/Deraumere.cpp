/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Deraumere
*/

#include "Deraumere.hpp"

#include <raymath.h>


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Deraumere::Deraumere(Vector3 position, float scale, Color color)
    : AItem(position, scale, color)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = LoadModel("assets/deraumere/scene.gltf");

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model.transform = MatrixMultiply(scaleMatrix, rotationMatrix);
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
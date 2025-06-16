/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Linemate
*/

#include "Linemate.hpp"

#include <raymath.h>


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Linemate::Linemate(Vector3 position, float scale, Color color)
    : AItem(position, scale, color)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = LoadModel("assets/linemate/scene.gltf");

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model.transform = MatrixMultiply(scaleMatrix, rotationMatrix);
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
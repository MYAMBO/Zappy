/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Mendiane
*/

#include "Mendiane.hpp"

#include <raymath.h>


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Mendiane::Mendiane(Vector3 position, float scale, Color color)
    : AItem(position, scale, color)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = LoadModel("assets/mendiane/scene.gltf");

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model.transform = MatrixMultiply(scaleMatrix, rotationMatrix);
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
/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Thystame
*/

#include "Thystame.hpp"

#include <raymath.h>


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Thystame::Thystame(Vector3 position, float scale, Color color)
    : AItem(position, scale, color)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = LoadModel("assets/thystame/scene.gltf");

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model.transform = MatrixMultiply(scaleMatrix, rotationMatrix);
}

gui::Thystame::~Thystame()
{
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


std::string gui::Thystame::getType()
{
    return "Thystame";
}
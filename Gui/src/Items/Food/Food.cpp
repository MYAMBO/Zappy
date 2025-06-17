/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Food
*/

#include "Food.hpp"

#include <raymath.h>

#include "Logger.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Food::Food(Vector3 position, float scale, Color color)
    : AItem(position, scale, color)
{
    float randomRotationY = (float)GetRandomValue(0, 360) * DEG2RAD;
    _model = LoadModel("assets/food/scene.gltf");

    Matrix scaleMatrix = MatrixScale(_scale, _scale, _scale);
    Matrix rotationMatrix = MatrixRotateY(randomRotationY);
    
    _model.transform = MatrixMultiply(scaleMatrix, rotationMatrix);
    Debug::InfoLog("Loading model Food: " + std::to_string(_model.meshCount) + " meshes");
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
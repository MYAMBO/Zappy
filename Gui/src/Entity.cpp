#include <iostream>
#include "../include/AEntity.hpp"

Gui::AEntity::AEntity(std::string type, Vector3 position, float scale, Color color)
{
    std::cout << "test" << std::endl;

    if (type == "Kayu") {
        Mesh mesh = GenMeshSphere(0.05f, 10, 500);
        _model = LoadModelFromMesh(mesh);
    } else {
        Mesh mesh = GenMeshCylinder(0.25f, 1.0f, 50);
        _model = LoadModelFromMesh(mesh);
    }

    std::cout << "tourte" << std::endl;
    _position = position;
    _scale = scale;
    _color = color;
}

Gui::AEntity::~AEntity()
{
    UnloadModel(_model);
}

Color Gui::AEntity::getColor()
{
    return _color;
}

Model Gui::AEntity::getModel()
{
    return _model;
}

Vector3 Gui::AEntity::getPosition()
{
    return _position;
}

float Gui::AEntity::getScale()
{
    return _scale;
}

void Gui::AEntity::setColor(Color color)
{
    _color = color;
}

void Gui::AEntity::setModel(Model model)
{
    UnloadModel(_model);
    _model = model;
}

void Gui::AEntity::setPosition(Vector3 position)
{
    _position = position;
}

void Gui::AEntity::setScale(float scale)
{
    _scale = scale;
}

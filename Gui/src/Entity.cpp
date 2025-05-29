/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Entity.cpp
*/

#include <iostream>
#include "../include/AEntity.hpp"

Gui::AEntity::AEntity(std::string type, Vector3 position, float scale, Color color)
{
    auto modelDeleter = [](Model* m) {
        UnloadModel(*m);
        delete m;
    };

    if (type == "Kayu") {
        Mesh mesh = GenMeshSphere(0.05f, 10, 500);
        this->_model = std::shared_ptr<Model>(new Model(LoadModelFromMesh(mesh)), modelDeleter);
    } else {
        Mesh mesh = GenMeshCylinder(0.5, 1, 50);
        this->_model = std::shared_ptr<Model>(new Model(LoadModelFromMesh(mesh)), modelDeleter);
    }

    this->_position = position;
    this->_scale = scale;
    this->_color = color;
}

Gui::AEntity::~AEntity() = default;

Color Gui::AEntity::getColor()
{
    return this->_color;
}

std::shared_ptr<Model> Gui::AEntity::getModel()
{
    return this->_model;
}

Vector3 Gui::AEntity::getPosition()
{
    return this->_position;
}

float Gui::AEntity::getScale()
{
    return this->_scale;
}

void Gui::AEntity::setColor(Color color)
{
    this->_color = color;
}

void Gui::AEntity::setModel(std::shared_ptr<Model> model)
{
    this->_model = model;
}

void Gui::AEntity::setPosition(Vector3 position)
{
    this->_position = position;
}

void Gui::AEntity::setScale(float scale)
{
    this->_scale = scale;
}

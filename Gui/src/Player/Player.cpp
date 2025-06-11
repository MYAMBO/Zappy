/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.cpp
*/

#include <raylib.h>

#include "Player.hpp"
#include "Logger.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Player::Player(Vector3 position, float scale, Color color, int screenWidth, int screenHeight)
    : AEntity("Player", position, scale, color),  _direction(North),  _inventory(screenWidth, screenHeight)
{
    Debug::InfoLog("[GUI] Player initialized: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z));
}

gui::Player::~Player() = default;


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/


void gui::Player::draw()
{
    DrawModel(_model, _position, _scale, _color);

    if (_isSelected) {
        DrawCubeWires(_position, _scale, _scale, _scale, {255, 0, 0, 255});
    }
}

void gui::Player::drawInventory()
{
    if (_toogleInventory && _isSelected) {
        _inventory.draw();
    }
}

int gui::Player::update(Camera3D camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        BoundingBox box = {
            { _position.x - _scale/4, _position.y - _scale/4, _position.z - _scale/4 },
            { _position.x + _scale/4, _position.y + _scale/4, _position.z + _scale/4 }
        };
        RayCollision collision = GetRayCollisionBox(ray, box);
        if (collision.hit) {
            _isSelected = true;
            Debug::InfoLog("[GUI] Player selected via ray picking");
        } else {
            _toogleInventory = false;
            _isSelected = false;
        }
    }
    if (_isSelected && IsKeyPressed(KEY_I)) {
        _toogleInventory = !_toogleInventory;
        Debug::InfoLog("[GUI] Inventory toggled: " + std::to_string(_toogleInventory));
    }

    return 0;
}


void gui::Player::Left()
{
    switch (this->_direction) {
        case North:
            this->_direction = West;
            break;
        case Est:
            this->_direction = North;
            break;
        case South:
            this->_direction = Est;
            break;
        case West:
            this->_direction = South;
            break;
    }
}

void gui::Player::Right() {
    switch (this->_direction) {
        case North:
            this->_direction = Est;
            break;
        case Est:
            this->_direction = South;
            break;
        case South:
            this->_direction = West;
            break;
        case West:
            this->_direction = North;
            break;
    }
}

void gui::Player::forward()
{
    float x = this->_position.x;
    float y = this->_position.y;
    float z = this->_position.z;

    switch (this->_direction) {
        case North:
            this->_position = {x, y, z + 1};
            break;
        case Est:
            this->_position = {x - 1, y, z};
            break;
        case South:
            this->_position = {x, y, z - 1};
            break;
        case West:
            this->_position = {x + 1, y, z};
            break;
    }
}

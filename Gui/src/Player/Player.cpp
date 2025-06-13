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


gui::Player::Player(Vector3 position, float scale, Color color, int screenWidth, int screenHeight, Camera3D &camera, int &sceneState)
    : AEntity(position, scale, color), _camButton([this, &camera, &sceneState]() { HandleCamButton(camera, sceneState); },
    Rectangle{0, static_cast<float>(screenHeight - 70), 150, 70}, "Camera"), _direction(North), _inventory(screenWidth, screenHeight)
{
    Mesh mesh = GenMeshCylinder(0.25f, 1.0f, 50);
    _model = LoadModelFromMesh(mesh);
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

void gui::Player::drawUI()
{
    if (_isSelected) {
        _inventory.draw();
        _camButton.draw();
    }
}

void gui::Player::updateUI()
{
    if (_isSelected) {
        _camButton.update();
    }
}

int gui::Player::update(Camera3D camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Debug::InfoLog("[GUI] Player clicked");
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
            Vector2 mousePos = GetMousePosition();
            Rectangle bounds = _camButton.getBounds();
            if (!(mousePos.x >= bounds.x && mousePos.x <= bounds.x + bounds.width &&
                  mousePos.y >= bounds.y && mousePos.y <= bounds.y + bounds.height))
                _isSelected = false;
        }
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

void gui::Player::HandleCamButton(Camera3D &camera, int &sceneState)
{
    Debug::InfoLog("[GUI] Camera button clicked");
    Debug::InfoLog("[GUI] Current position: x = " + std::to_string(_position.x) +
                   ", y = " + std::to_string(_position.y) + ", z = " + std::to_string(_position.z));
    camera = { { _position.x - 2, _position.y + 2, _position.z - 2 },
        { _position.x, _position.y, _position.z },
        { 0.0f, 1.0f, 0.0f },
        45.0f,
        0 };
    sceneState = 2;
}
/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.cpp
*/

#include <raylib.h>
#include <utility>
#include "Player.hpp"
#include "Logger.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/

gui::Player::Player(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team, float scale,
                    int screenWidth, int screenHeight, Camera3D &camera, int &sceneState) :
                    AEntity({(float)position.first, 0, (float)position.second}, scale, WHITE), _id(id), _direction(orientation), _level(level), _team(std::move(team)),
                    _camButton([this, &camera, &sceneState]() { HandleCamButton(camera, sceneState); }, Rectangle{0, static_cast<float>(screenHeight - 70), 150, 70}, "Camera"),
                    _inventory(screenWidth, screenHeight)
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

int gui::Player::getId() const
{
    return this->_id;
}

int gui::Player::getLevel() const
{
    return this->_level;
}

Orientation gui::Player::getOrientation() const
{
    return this->_direction;
}

std::string gui::Player::getTeam() const
{
    return  this->_team;
}

void gui::Player::setLevel(int level)
{
    this->_level = level;
}

void gui::Player::setOrientation(Orientation orientation)
{
    this->_direction = orientation;
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
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


gui::Player::Player(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team, float scale, int screenWidth, int screenHeight, Camera3D &camera, CamState &sceneState)
    : AEntity({(float)position.first, 0.5, (float)position.second}, scale, RED), _id(id), _level(level), _team(std::move(team)),
    _camButton([this, &camera, &sceneState]() { HandleCamButton(camera, sceneState); }, Rectangle{0, static_cast<float>(screenHeight - 70), 150, 70}, "Camera"),
    _direction(orientation), _inventory(screenWidth, screenHeight)
{
    Mesh mesh = GenMeshCylinder(0.25f, 1.0f, 50);
    this->_model = std::make_unique<Model>(LoadModelFromMesh(mesh));

}

gui::Player::~Player() = default;


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/


void gui::Player::draw()
{
    DrawModel(*this->_model, this->_position, this->_scale, this->_color);

    if (_isSelected) {
        DrawCubeWires(this->_position, this->_scale, this->_scale, this->_scale, {255, 0, 0, 255});
    }
}

void gui::Player::drawUI()
{
    if (this->_isSelected) {
        this->_inventory.draw();
        this->_camButton.draw();
    }
}

void gui::Player::updateUI()
{
    if (this->_isSelected) {
        this->_camButton.update();
    }
}

int gui::Player::update(Camera3D camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        BoundingBox box = {
            { this->_position.x - this->_scale/4, this->_position.y - this->_scale/4, this->_position.z - this->_scale/4 },
            { this->_position.x + this->_scale/4, this->_position.y + this->_scale/4, this->_position.z + this->_scale/4 }
        };
        RayCollision collision = GetRayCollisionBox(ray, box);
        if (collision.hit) {
            _isSelected = true;
            Debug::InfoLog("[GUI] Player selected via ray picking");
        } else {
            Vector2 mousePos = GetMousePosition();
            Rectangle bounds = this->_camButton.getBounds();
            if (!(mousePos.x >= bounds.x && mousePos.x <= bounds.x + bounds.width &&
                  mousePos.y >= bounds.y && mousePos.y <= bounds.y + bounds.height))
                this->_isSelected = false;
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

void gui::Player::HandleCamButton(Camera3D &camera, CamState &sceneState)
{
    camera = { { this->_position.x - 2, this->_position.y + 2, this->_position.z - 2 },
        { this->_position.x, this->_position.y, this->_position.z },
        { 0.0f, 1.0f, 0.0f },
        45.0f,
        0 };
    sceneState = CamState::PLAYER;
}
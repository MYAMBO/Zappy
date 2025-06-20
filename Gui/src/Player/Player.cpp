/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.cpp
*/

#include <utility>
#include <raylib.h>
#include <raymath.h>

#include "Player.hpp"
#include "Logger.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Player::Player(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team,
        float scale, int screenWidth, int screenHeight, Camera3D &camera, CamState &sceneState)
    : AEntity({(float)position.first, 0.5, (float)position.second}, scale, WHITE), 
    _id(id), _level(level), _currentAnim(0), _animFrameCounter(0), _isMoving(false), _isSelected(false), _team(std::move(team)), _moveSpeed(2.0f), _animationSpeed(1.0f),
    _camButton([this, &camera, &sceneState]() { HandleCamButton(camera, sceneState); }, Rectangle{0, static_cast<float>(screenHeight - 70), 150, 70}, "Camera"),
    _inventory(screenWidth, screenHeight), _direction(orientation), _currentAnimState(AnimState::IDLE)
{
    _model = std::make_shared<Model>(LoadModel("assets/player/scene.gltf"));
    _animations = LoadModelAnimations("assets/player/scene.gltf", &_animCount);

    _model->transform = MatrixScale(scale, scale, scale);
}

gui::Player::~Player() = default;


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void gui::Player::startMoveTo(Vector3 newPosition)
{
    _targetPosition = newPosition;
    _isMoving = true;
    if (_animCount >= 2) {
        setAnimationState(AnimState::WALKING);
    }
}

void gui::Player::stopMoving()
{
    _isMoving = false;
    if (_animCount >= 1) {
        setAnimationState(AnimState::IDLE);
    }
}

void gui::Player::draw()
{
    if (_direction == Orientation::North)
        _rotationY = 0.0f;
    else if (_direction == Orientation::Est)
        _rotationY = 90.0f;
    else if (_direction == Orientation::South)
        _rotationY = 180.0f;
    else if (_direction == Orientation::West)
        _rotationY = 270.0f;
    DrawModelEx(*_model, _position, {0, 1, 0}, _rotationY, {_scale, _scale, _scale}, _color);
    if (_isSelected) {
        DrawCubeWires(_position, _scale, _scale, _scale, {255, 0, 0, 255});
    }
    broadcastAnimation();
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
    Debug::DebugLog("Position: " + std::to_string(_position.x) + ", " + std::to_string(_position.y) + ", " + std::to_string(_position.z));
    if (_isMoving) {
        Vector3 direction = Vector3Subtract(_targetPosition, _position);
        float distance = Vector3Length(direction);
        if (distance > 0.1f) {
            direction = Vector3Normalize(direction);
            _position = Vector3Add(_position, Vector3Scale(direction, _moveSpeed * GetFrameTime()));
        } else {
            _position = _targetPosition;
            stopMoving();
        }
    }
    if (_animCount > 0 && _animations && _currentAnim < _animCount) {
        _animFrameCounter++;
        if (_animFrameCounter >= _animations[_currentAnim].frameCount)
            _animFrameCounter = 0;
        UpdateModelAnimation(*_model, _animations[_currentAnim], _animFrameCounter);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        BoundingBox box = {
            { _position.x - _scale/4, _position.y - _scale/4, _position.z - _scale/4 },
            { _position.x + _scale/4, _position.y + _scale/4, _position.z + _scale/4 }
        };
        RayCollision collision = GetRayCollisionBox(ray, box);
        if (collision.hit) {
            _isSelected = true;
        } else {
            Vector2 mousePos = GetMousePosition();
            Rectangle bounds = _camButton.getBounds();
            if (!(mousePos.x >= bounds.x && mousePos.x <= bounds.x + bounds.width &&
                  mousePos.y >= bounds.y && mousePos.y <= bounds.y + bounds.height))
                _isSelected = false;
        }
    }
    if (IsKeyPressed(KEY_ESCAPE))
        _isSelected = false;
    
    return 0;
}

void gui::Player::HandleCamButton(Camera3D &camera, CamState &sceneState)
{
    camera = { { _position.x - 2, _position.y + 2, _position.z - 2 },
        { _position.x, _position.y, _position.z },
        { 0.0f, 1.0f, 0.0f },
        45.0f,
        0 };
    sceneState = CamState::PLAYER;
}

void gui::Player::broadcastAnimation()
{
    if (!_isBroadcasting)
        return;
    _broadcastTimer += GetFrameTime();
    float t = _broadcastTimer / _broadcastDuration;
    if (t > 1.0f) {
        _isBroadcasting = false;
        return;
    }
    float scale = Lerp(0.5f, 9.0f, t);
    float alpha = Lerp(0.8f, 0.0f, t);
    Color color = { 0, 150, 255, static_cast<unsigned char>(alpha * 255) };
    Vector3 pos = getPosition();
    DrawSphere(pos, scale, color);
}


/************************************************************
**              >>>>   GETTERS FUNCTIONS   <<<<            **
************************************************************/


std::string gui::Player::getTeam() const
{
    return  _team;
}

int gui::Player::getId() const
{
    return _id;
}

int gui::Player::getLevel() const
{
    return _level;
}

Orientation gui::Player::getOrientation() const
{
    return _direction;
}

bool gui::Player::getSelected() const
{
    return _isSelected;
}

bool gui::Player::getIsMoving() const
{
    return _isMoving;
}


/************************************************************
**              >>>>   SETTERS FUNCTIONS   <<<<            **
************************************************************/


void gui::Player::setLevel(int level)
{
    _level = level;
}

void gui::Player::setOrientation(Orientation orientation)
{
    _direction = orientation;
}

void gui::Player::setAnimationSpeed(float speed)
{
    _animationSpeed = speed;
}

void gui::Player::setAnimationState(AnimState newState)
{
    if (_currentAnimState != newState && _animCount > static_cast<int>(newState)) {
        _currentAnimState = newState;
        _currentAnim = static_cast<int>(newState);
        _animFrameCounter = 0;
    }
}

void gui::Player::setBroadcasting(bool broadcasting)
{
    _isBroadcasting = broadcasting;
    if (broadcasting) {
        _broadcastTimer = 0.0f;
    }
}
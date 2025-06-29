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
        float scale, int screenWidth, int screenHeight, Camera &camera, CamState &sceneState, std::shared_ptr<int> timeUnit,
        std::shared_ptr<Model> model, Model deadModel, ModelAnimation *animations, int animCount, std::shared_ptr<Model> teamModel)
    : AEntity({(float)position.first, 1.0f, (float)position.second}, scale, WHITE), 
    _model(model), _id(id), _level(level), _animCount(animCount), _currentAnim(2), _animFrameCounter(0), _isMoving(false), _isSelected(false), _team(std::move(team)), _animationSpeed(1.0f),
    _camButton([this, &camera, &sceneState]() { HandleCamButton(camera, sceneState); }, Rectangle{0, static_cast<float>(screenHeight - 70), 150, 70}, "Camera"),
    _inventory(std::make_shared<gui::ui::Inventory>(screenWidth, screenHeight)), _deadModel(deadModel), _direction(orientation), _currentAnimState(AnimState::IDLE),
    _animations(animations), _teamModel(teamModel)
{
    _mutex.lock();

    _timeUnit = timeUnit;
    if (_animCount > 0) {
        _currentAnim = 0;
        _animFrameCounter = 0;
        setAnimationState(AnimState::IDLE);
    }
    _model->transform = MatrixScale(scale, scale, scale);
    _playersNames = {
        {0, "piairkiroulnamaszpamouss"},
        {1, "aportéçapiairalidifiss"},
        {2, "cassoeurdepiair"},
        {3, "fairdunepiairdecou"},
        {4, "piairafeu"},
        {5, "piairfilosofale"},
        {6, "jeunevoujaitepalapiarpiair"},
        {7, "robespiair"},
        {8, "tailleurdepièr"},
        {9, "piairgeantdeukarpantri"},
        {10, "geanPiair"},
        {11, "pièrdemèere"},
        {12, "pièrponsse"},
        {13, "piairninez"},
        {14, "pièrpraissieuze"},
        {15, "piairdelastarac"},
        {16, "piérkifédelatutureéboompula"},
        {17, "piairfeuilsizo"},
        {18, "piairrauchar"},
        {19, "piairshabriaicontedementécristeau"},
        {20, "abépiair"},
        {21, "piairtonballe"},
        {22, "keuredepiair"},
        {23, "vodkayu"},
        {24, "kayulotre"},
        {25, "kakayu"},
        {26, "kayumoulox"},
        {27, "kayutube"},
        {28, "rocheboboi"},
        {29, "bazukayu"},
        {30, "babouchkayu"},
        {31, "kayuyak"},
        {32, "lençaideuxkayu"},
        {33, "petikayudenléshossur"},
        {34, "iverocher"},
        {35, "fereroroché"},
        {36, "zerock"},
        {37, "rockérole"},
        {38, "barock"},
        {39, "crockcarote"},
        {40, "rockète"},
        {41, "rocksthar"},
        {42, "prockureurdelaraiepublic"},
        {43, "gelamédenmonchapoélmedikifétrochojelamédenmontiroireélmedikifétronoirgelamédenmakuloteélmefétroipetitekrock"},
        {44, "jéchiaidanmonfrock"},
        {45, "interstonar"},
        {46, "stonanalizis"},
        {47, "gaymoffstaunne"},
        {48, "rolingstone"},
        {49, "emastone"},
        {50, "silvestonestaler"},
        {51, "aistoni"},
        {52, "stonitark"},
        {53, "rockibalbaua"}
    };
    _mutex.unlock();
}

gui::Player::~Player() = default;


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void gui::Player::startMoveTo(Vector3 newPosition)
{
    _targetPosition = newPosition;
    if (_targetPosition.x - _position.x > 1 || _targetPosition.x - _position.x < -1 ||
        _targetPosition.z - _position.z > 1 || _targetPosition.z - _position.z < -1) {
        _position = _targetPosition;
        return;
    }
    if (*_timeUnit >= 200) {
        _position = _targetPosition;
        return;
    }
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
    if (_isDead) {
        if (_countBeforeExpire > 0) {
            DrawModelEx(_deadModel, {_position.x, _position.y - 0.5f, _position.z}, {0, 1, 0}, _rotationY, {0.01f, 0.01f, 0.01f}, WHITE);
            _countBeforeExpire--;
        }
        return;
    }
    if (_direction == Orientation::North)
        _rotationY = 180.0f;
    else if (_direction == Orientation::Est)
        _rotationY = 90.0f;
    else if (_direction == Orientation::South)
        _rotationY = 0.0f;
    else if (_direction == Orientation::West)
        _rotationY = 270.0f;
    UpdateModelAnimation(*_model, _animations[_currentAnim], _animFrameCounter);
    DrawModelEx(*_model, _position, {0, 1, 0}, _rotationY, {_scale, _scale, _scale}, WHITE);
    if (_isSelected)
        DrawCubeWires(_position, 1, 1, 1, {255, 0, 0, 255});
    broadcastAnimation();
    IncantationAnimation();
    DrawModelEx(*_teamModel, {_position.x, _position.y + 0.8f, _position.z}, {0, 1, 0}, _rotationY, {0.05, 0.05, 0.05}, _colorTeam->operator[](_team));
}

void gui::Player::drawUI()
{
    if (_isSelected) {
        _inventory->draw();
        DrawText(("Team name: " + _team).c_str(), static_cast<float>(SCREEN_WIDTH) / 5.0f, static_cast<float>(SCREEN_HEIGHT) * 0.8f + 10, 30, _colorTeam->operator[](_team));
        DrawText(("Player ID: " + std::to_string(_id)).c_str(), static_cast<float>(SCREEN_WIDTH) / 2.8, static_cast<float>(SCREEN_HEIGHT) * 0.8f + 10, 30, _colorTeam->operator[](_team));
        int falseId = _id;
        int counter = 0;
        if (falseId > static_cast<int>(_playersNames.size())) {
            while (falseId >= static_cast<int>(_playersNames.size())) {
                counter++;
                falseId -= _playersNames.size();
            }
        }
        if (counter == 0)
            DrawText(("Player name: " + _playersNames[falseId]).c_str(), static_cast<float>(SCREEN_WIDTH) / 2, static_cast<float>(SCREEN_HEIGHT) * 0.8f + 10, 30, _colorTeam->operator[](_team));
        else 
            DrawText(("Player name: " + _playersNames[falseId] + " " + std::to_string(counter)).c_str(), static_cast<float>(SCREEN_WIDTH) / 2, static_cast<float>(SCREEN_HEIGHT) * 0.8f + 10, 30, _colorTeam->operator[](_team));
        DrawText(("Level: " + std::to_string(_level)).c_str(), static_cast<float>(SCREEN_WIDTH) / 1.2, static_cast<float>(SCREEN_HEIGHT) * 0.8f + 10, 30, _colorTeam->operator[](_team));
        _camButton.draw();
    }
}

void gui::Player::updateUI()
{
    if (_isSelected) {
        _camButton.update();
    }
}

void gui::Player::updateMovementAndAnimation()
{
    if (_isMoving) {
        Vector3 direction = Vector3Subtract(_targetPosition, _position);
        float distance = Vector3Length(direction);
        if (distance > 0.1f) {
            direction = Vector3Normalize(direction);
            _position = Vector3Add(_position, Vector3Scale(direction, (1.0f/static_cast<float>(*_timeUnit) * 2)));
        } else {
            _position = _targetPosition;
            stopMoving();
        }
    }
    if (_animCount > 0 && _currentAnim < _animCount) {
        _animFrameCounter++;
        if (_animFrameCounter >= _animations[_currentAnim].frameCount) {
            _animFrameCounter = 0;
        }
        UpdateModelAnimation(*_model, _animations[_currentAnim], _animFrameCounter);
    }
}

int gui::Player::handleUserInput(Camera camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsKeyDown(KEY_LEFT_SHIFT)) {
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        BoundingBox box = {
            { _position.x - 0.5f, _position.y - 0.5f, _position.z - 0.5f},
            { _position.x + 0.5f, _position.y + 0.5f, _position.z + 0.5f}
        };
        RayCollision collision = GetRayCollisionBox(ray, box);
        if (collision.hit) {
            _isSelected = true;
            return 1;
        } else {
            Vector2 mousePos = GetMousePosition();
            Rectangle bounds = _camButton.getBounds();
            if (!(mousePos.x >= bounds.x && mousePos.x <= bounds.x + bounds.width &&
                  mousePos.y >= bounds.y && mousePos.y <= bounds.y + bounds.height))
                _isSelected = false;
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_SHIFT)) {
        _isSelected = false;
    }
    if (IsKeyPressed(KEY_ESCAPE))
        _isSelected = false;
    return 0;
}

int gui::Player::update(Camera camera)
{
    updateMovementAndAnimation();
    if (handleUserInput(camera) == 1)
        return 1;
    return 0;
}

void gui::Player::HandleCamButton(Camera &camera, CamState &sceneState)
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

void gui::Player::IncantationAnimation()
{
    if (!_isIncantation && !_isIncantationEnded)
        return;
    if (_isIncantationEnded) {
        _IncantationTimer += GetFrameTime();
        float t = _IncantationTimer / _IncantationDuration;
        if (t > 1.0f) {
            _isIncantationEnded = false;
            return;
        }
        float scale = Lerp(0.5f, 9.0f, t);
        float alpha = Lerp(0.8f, 0.0f, t);
        Color color = { 255, 255, 0, static_cast<unsigned char>(alpha * 255) };
        Vector3 pos = getPosition();
        DrawCube(pos, scale, scale, scale, color);
        return;
    }
    _IncantationTimer += GetFrameTime();
    float t = _IncantationTimer / _IncantationDuration;
    if (t > 1.0f) {
        _isIncantation = false;
        return;
    }
    float scale = Lerp(0.5f, 9.0f, t);
    float alpha = Lerp(0.8f, 0.0f, t);
    Color color = { 75, 0, 130, static_cast<unsigned char>(alpha * 255) };
    Vector3 pos = getPosition();
    DrawCube(pos, scale, scale, scale, color);
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

gui::Orientation gui::Player::getOrientation() const
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


void gui::Player::setColorTeam(std::shared_ptr<std::map<std::string, Color>> colorTeam)
{
    _colorTeam = colorTeam;
    _color = _colorTeam->operator[](_team);
}

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
    if  (_animCount > static_cast<int>(newState)) {
        _currentAnimState = newState;
        _currentAnim = static_cast<int>(newState);
        _animFrameCounter = 0;
    }
}

void gui::Player::setBroadcasting(bool broadcasting)
{
    _isBroadcasting = broadcasting;
    if (broadcasting)
        _broadcastTimer = 0.0f;
}

void gui::Player::setisDead(bool isDead)
{
    _isDead = isDead;
}

void gui::Player::setInventory(const std::string item, int quantity)
{
    _inventory->setInventoryItem(item, quantity);
}

void gui::Player::setIncantation(bool isIncantation)
{
    _isIncantation = isIncantation;
    if (_isIncantation)
        _IncantationTimer = 0.0f;
}

void gui::Player::setIncantationEnded(bool isIncantationEnded)
{
    _isIncantationEnded = isIncantationEnded;
    if (_isIncantationEnded)
        _IncantationTimer = 0.0f;
}

void gui::Player::setSelected(bool selected)
{
    _isSelected = selected;
}
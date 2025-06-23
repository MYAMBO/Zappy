/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/
#include <math.h>

#include "Menu.hpp"
#include "Scene.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Client.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Scene::Scene()
    : _camState(CamState::WORLD), _isOpen(true), _width(WIDTH), _height(HEIGHT), _currentState(SceneState::MENU), _models() //don't forget here
{
    Debug::ClearLogFile();
    Debug::InfoLog("Zappy started");
    initWindow();

    // remove later from here

    this->_models.emplace_back(safeModelLoader("assets/food/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/linemate/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/deraumere/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/sibur/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/mendiane/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/phiras/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/thystame/scene.gltf"));

    // to here

    _menu = std::make_unique<gui::ui::Menu>(_currentState, SCREEN_WIDTH, SCREEN_HEIGHT);
    _settings = std::make_unique<gui::ui::Settings>(_currentState, SCREEN_WIDTH, SCREEN_HEIGHT);
    _itemDisplay = {1, 1, 1, 1, 1, 1, 1};
    _menu->initMenuUI();
    _settings->initSettingsUI();
    _eggs.emplace_back(std::make_shared<gui::Egg>(0, std::make_pair(GetRandomValue(0, WIDTH - 1), GetRandomValue(0, HEIGHT - 1))));

    SetPlayers(this->_players);
    SetMap(this->_map);
}

gui::Scene::~Scene()
{
    CloseWindow();
}


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/


void gui::Scene::initWindow()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zappy");
    SetTargetFPS(TARGET_FPS);

    this->_camera = { { -_width, 10.0f, -_height}, { _width / 2, 0.0f, _height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
}

void gui::Scene::displayEntity()
{
    for (auto& tile : _map) {
        tile->displayTile(_itemDisplay);
    }
    for (auto& player : _players) {
        player->draw();
    }
    for (auto& egg : _eggs) {
        egg->draw();
    }
}

void gui::Scene::initOrbitalCamera(const Vector3& target, float distance)
{
    float theta = 45.0f * DEG2RAD;
    float phi = 30.0f * DEG2RAD;

    _camera.target = target;
    _camera.position = {
        target.x + distance * cosf(phi) * cosf(theta),
        target.y + distance * sinf(phi),
        target.z + distance * cosf(phi) * sinf(theta)
    };
    _camera.up = {0.0f, 1.0f, 0.0f};
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
}


void gui::Scene::handleInput()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (_camState == CamState::WORLD) {
            _currentState = SceneState::MENU;
        }
        else if (_camState == CamState::PLAYER) {
            _camera = { { -_width, 10.0f, -_height}, { _width / 2, 0.0f, _height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
            _camState = CamState::WORLD;
        }
    }
    for (auto& player : _players)
        player->update(_camera);
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        if (_camState == CamState::WORLD) {
            UpdateCamera(&_camera, CAMERA_THIRD_PERSON);
        }
        else if (_camState == CamState::PLAYER) {
            for (auto& player : _players) {
                if (player->getSelected() && !player->getIsMoving()) {
                    UpdateCamera(&_camera, CAMERA_ORBITAL);
                }
            }
        }
    }
    if (_camState == CamState::PLAYER) {
        for (auto& player : _players) {
            if (player->getSelected()) {
                if (player->getIsMoving()) {
                    _camera.target = player->getPosition();
                    _camera.position = {
                        player->getPosition().x - 2.0f,
                        player->getPosition().y + 2.0f,
                        player->getPosition().z - 2.0f
                    };
                }
            }
        }
    }
}

void gui::Scene::render()
{
    BeginDrawing();
    if (_camera.position.y < 0.1f) {
        _camera.position.y = 0.1f;
    }
    ClearBackground(BLACK);
    BeginMode3D(_camera);
    displayEntity();
    EndMode3D();
    for (auto& player : _players) {
        player->drawUI();
        player->updateUI();
    }
    EndDrawing();
}

bool gui::Scene::isOpen() const
{
    return _isOpen;
}

void gui::Scene::update()
{
    if (!_isOpen) {
        return;
    }
    switch (_currentState) {
        case SceneState::GAME:
            eventToggleDisplay();
            handleInput();
            render();
            if (IsKeyPressed(KEY_J)) {
                _players[0]->startMoveTo({static_cast<float>(GetRandomValue(0, (int)WIDTH - 1)), 1.0f, static_cast<float>(GetRandomValue(0, (int)HEIGHT - 1))});
                //_players[0]->setBroadcasting(true);
                //_players[0]->setisDead(true);
            }
            break;
        case SceneState::EXIT:
            Debug::InfoLog("[GUI] Exit state reached, closing window");
            _isOpen = false;
            break;
        case SceneState::MENU:
            _menu->handleMenuInput();
            _menu->drawMainMenu();
            break;
        case SceneState::SETTINGS:
            _settings->handleSettingsInputs();
            _settings->drawSettings();
            break;
    }
}

std::shared_ptr<Model> gui::Scene::safeModelLoader(const std::string& string)
{
    std::cout << string << std::endl;
    std::shared_ptr<Model> model = std::make_shared<Model>(LoadModel(string.c_str()));

    if (model->meshCount == 0 || model->meshes == nullptr)
        throw gui::FailedLoadModel();

    return model;
}

void gui::Scene::eventToggleDisplay()
{
    if (IsKeyPressed(KEY_ONE)) {
        if (_itemDisplay[gui::Tile::FOOD] == 0) {
            _itemDisplay[gui::Tile::FOOD] = 1;
        } else {
            _itemDisplay[gui::Tile::FOOD] = 0;
        }
    }
    if (IsKeyPressed(KEY_TWO)) {
        if (_itemDisplay[gui::Tile::LINEMATE] == 0) {
            _itemDisplay[gui::Tile::LINEMATE] = 1;
        } else {
            _itemDisplay[gui::Tile::LINEMATE] = 0;
        }
    }
    if (IsKeyPressed(KEY_THREE)) {
        if (_itemDisplay[gui::Tile::DERAUMERE] == 0) {
            _itemDisplay[gui::Tile::DERAUMERE] = 1;
        } else {
            _itemDisplay[gui::Tile::DERAUMERE] = 0;
        }
    }
    if (IsKeyPressed(KEY_FOUR)) {
        if (_itemDisplay[gui::Tile::SIBUR] == 0) {
            _itemDisplay[gui::Tile::SIBUR] = 1;
        } else {
            _itemDisplay[gui::Tile::SIBUR] = 0;
        }
    }
    if (IsKeyPressed(KEY_FIVE)) {
        if (_itemDisplay[gui::Tile::MENDIANE] == 0) {
            _itemDisplay[gui::Tile::MENDIANE] = 1;
        } else {
            _itemDisplay[gui::Tile::MENDIANE] = 0;
        }
    }
    if (IsKeyPressed(KEY_SIX)) {
        if (_itemDisplay[gui::Tile::PHIRAS] == 0) {
            _itemDisplay[gui::Tile::PHIRAS] = 1;
        } else {
            _itemDisplay[gui::Tile::PHIRAS] = 0;
        }
    }
    if (IsKeyPressed(KEY_SEVEN)) {
        if (_itemDisplay[gui::Tile::THYSTAME] == 0) {
            _itemDisplay[gui::Tile::THYSTAME] = 1;
        } else {
            _itemDisplay[gui::Tile::THYSTAME] = 0;
        }
    }
}

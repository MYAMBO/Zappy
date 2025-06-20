/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/

#include "Menu.hpp"
#include "Scene.hpp"
#include "Player.hpp"
#include "Settings.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Scene::Scene()
    : _camState(CamState::WORLD), _isOpen(true), _width(WIDTH), _height(HEIGHT), _currentState(SceneState::MENU), _models()
{
    Debug::ClearLogFile();
    Debug::InfoLog("Zappy started");
    initWindow();
    
    _models.emplace_back(safeModelLoader("assets/food/scene.gltf"));
    _models.emplace_back(safeModelLoader("assets/linemate/scene.gltf"));
    _models.emplace_back(safeModelLoader("assets/deraumere/scene.gltf"));
    _models.emplace_back(safeModelLoader("assets/sibur/scene.gltf"));
    _models.emplace_back(safeModelLoader("assets/mendiane/scene.gltf"));
    _models.emplace_back(safeModelLoader("assets/phiras/scene.gltf"));
    _models.emplace_back(safeModelLoader("assets/thystame/scene.gltf"));
    
    _menu = std::make_unique<gui::ui::Menu>(_currentState, SCREEN_WIDTH, SCREEN_HEIGHT);
    _settings = std::make_unique<gui::ui::Settings>(_currentState, SCREEN_WIDTH, SCREEN_HEIGHT);
    _itemDisplay = {1, 1, 1, 1, 1, 1, 1};
    _menu->initMenuUI();
    _settings->initSettingsUI();
    initMap();
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

    _camera = { { -_width, 10.0f, -_height}, { _width / 2, 0.0f, _height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
}

void gui::Scene::initMap()
{
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            std::pair<int, int> coord = {x, y};

            std::vector<int> qty;

            qty.emplace_back(1);
            qty.emplace_back(1);
            qty.emplace_back(1);
            qty.emplace_back(1);
            qty.emplace_back(1);
            qty.emplace_back(1);
            qty.emplace_back(1);

            _map.emplace_back(std::make_shared<gui::Tile>(coord, qty, _models));
        }
    }
    for (int x = 0; (float)x < 10; ++x) {
        std::pair<int, int> coord = {GetRandomValue(0, (int)WIDTH - 1), GetRandomValue(0, (int)HEIGHT - 1)};
        _players.emplace_back(std::make_shared<gui::Player>(x, coord, North, 1, "toto", 1, SCREEN_WIDTH, SCREEN_HEIGHT, _camera, _camState));
    }
}

void gui::Scene::displayEntity()
{
    for (auto& tile : _map) {
        tile->displayTile(_itemDisplay);
    }
    for (auto& player : _players) {
        player->draw();
    }
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
            UpdateCamera(&_camera, CAMERA_ORBITAL);
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
            Debug::InfoLog("[GUI] Food display toggled");
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

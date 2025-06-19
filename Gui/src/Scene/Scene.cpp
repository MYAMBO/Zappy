/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/

#include "Menu.hpp"
#include "Scene.hpp"
#include "Player.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Scene::Scene()
    : _camState(CamState::WORLD), _isOpen(true), _width(WIDTH), _height(HEIGHT), _currentState(SceneState::GAME), _models()
{
    Debug::ClearLogFile();
    Debug::InfoLog("Zappy started");

    initWindow();

    this->_models.emplace_back(safeModelLoader("assets/food/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/linemate/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/deraumere/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/sibur/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/mendiane/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/phiras/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/thystame/scene.gltf"));

    _menu = std::make_unique<gui::ui::Menu>(_currentState, SCREEN_WIDTH, SCREEN_HEIGHT);
    _itemDisplay = {
        {"Food", 1},
        {"Linemate", 1},
        {"Deraumere", 1},
        {"Sibur", 1},
        {"Mendiane", 1},
        {"Phiras", 1},
        {"Thystame", 1}
    };
    _menu->initMenuUI();
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

            _map.emplace_back(std::make_shared<gui::Tile>(coord, qty, this->_models));
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
    return _isOpen && !WindowShouldClose();
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
            _isOpen = false;
            break;
        case SceneState::MENU:
            _menu->handleMenuInput();
            _menu->drawMainMenu();
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
    // when & is pressed
    if (IsKeyPressed(KEY_ONE)) {
        if (_itemDisplay["Food"] == 0) {
            _itemDisplay["Food"] = 1;
        } else {
            Debug::InfoLog("[GUI] Food display toggled");
            _itemDisplay["Food"] = 0;
        }
    }
    if (IsKeyPressed(KEY_TWO)) {
        if (_itemDisplay["Linemate"] == 0) {
            _itemDisplay["Linemate"] = 1;
        } else {
            _itemDisplay["Linemate"] = 0;
        }
    }
    if (IsKeyPressed(KEY_THREE)) {
        if (_itemDisplay["Deraumere"] == 0) {
            _itemDisplay["Deraumere"] = 1;
        } else {
            _itemDisplay["Deraumere"] = 0;
        }
    }
    if (IsKeyPressed(KEY_FOUR)) {
        if (_itemDisplay["Sibur"] == 0) {
            _itemDisplay["Sibur"] = 1;
        } else {
            _itemDisplay["Sibur"] = 0;
        }
    }
    if (IsKeyPressed(KEY_FIVE)) {
        if (_itemDisplay["Mendiane"] == 0) {
            _itemDisplay["Mendiane"] = 1;
        } else {
            _itemDisplay["Mendiane"] = 0;
        }
    }
    if (IsKeyPressed(KEY_SIX)) {
        if (_itemDisplay["Phiras"] == 0) {
            _itemDisplay["Phiras"] = 1;
        } else {
            _itemDisplay["Phiras"] = 0;
        }
    }
    if (IsKeyPressed(KEY_SEVEN)) {
        if (_itemDisplay["Thystame"] == 0) {
            _itemDisplay["Thystame"] = 1;
        } else {
            _itemDisplay["Thystame"] = 0;
        }
    }
}

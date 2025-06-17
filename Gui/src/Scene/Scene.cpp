/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/

#include "Scene.hpp"
#include "Player.hpp"

gui::Scene::Scene()
    : _camState(CamState::WORLD), _isOpen(true), _width(WIDTH), _height(HEIGHT), _currentState(SceneState::GAME)
{
    Debug::ClearLogFile();
    Debug::InfoLog("Zappy started");
    
    initWindow();
    initMap();
}

gui::Scene::~Scene()
{
    CloseWindow();
}

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
            int food = GetRandomValue(0, 2);
            int linemate = GetRandomValue(0, 2);
            int deraumere = GetRandomValue(0, 2);
            int sibur = GetRandomValue(0, 2);
            int mendiane = GetRandomValue(0, 2);
            int phiras = GetRandomValue(0, 2);
            int thystame = GetRandomValue(0, 2);

            _map.emplace_back(std::make_shared<gui::Tile>(coord, food, linemate, deraumere, sibur, mendiane, phiras, thystame));
        }
    }

    for (int x = 0; (float)x < 10; ++x) {
        std::pair<int, int> coord = {GetRandomValue(0, (int)WIDTH - 1), GetRandomValue(0, (int)HEIGHT - 1)};

        _players.emplace_back(std::make_shared<gui::Player>(x, coord, North, 1, "toto", 1, SCREEN_WIDTH, SCREEN_HEIGHT, _camera, _camState));
    }
}

void gui::Scene::displayMap()
{
    for (int x = 0; x < (int)_width; x++) {
        for (int z = 0; z < (int)_height; z++) {
            Vector3 position = { (float)x, -0.5f, (float)z };
            DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});
            DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
        }
    }
}

void gui::Scene::displayEntity()
{
    for (auto& tile : _map) {
        tile->displayTile();
    }
    for (auto& player : _players) {
        player->draw();
    }
}


void gui::Scene::handleInput()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (_camState == CamState::WORLD) {
            _currentState = SceneState::EXIT;
            _isOpen = false;
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
    displayMap();
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
            handleInput();
            render();
            break;
        case SceneState::EXIT:
            _isOpen = false;
            break;
    }
}

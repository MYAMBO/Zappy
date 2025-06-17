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
    initEntities();
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

void gui::Scene::initEntities()
{
    _players = std::vector<gui::Player>();
    _entities = std::vector<std::unique_ptr<gui::AItem>>();
    for (int x = 0; x < (int)((_width * _height) / 2); ++x) {
        int value1 = GetRandomValue(0, (int)_width - 1);
        int value2 = GetRandomValue(0, (int)_height - 1);
        int isKayu = GetRandomValue(0, 1);

        if (isKayu == 0) {
            // Create Food entity
            auto food = std::make_unique<gui::Food>(gui::Food({(float)value1, 0.05f, (float)value2}, 0.7f, BROWN));
            _entities.push_back(std::move(food));
        } else if (isKayu == 1) {
            // Create Player entity - use emplace_back to construct in place
            _players.emplace_back(gui::Player({(float)value1, 0.05f, (float)value2}, 0.5f, BROWN, SCREEN_WIDTH, SCREEN_HEIGHT, _camera, _camState));
        }
        //if (isKayu == 0)
        //    _entities.push_back(std::make_unique<gui::Food>(gui::Food({(float)value1, 0.05f, (float)value2}, 0.7f, BROWN)));
        //if (isKayu == 1)
        //    _players.push_back(gui::Player({(float)value1, 0.05f, (float)value2}, 0.5f, BROWN, SCREEN_WIDTH, SCREEN_HEIGHT, _camera, _camState));
        //if (isKayu == 2)
        //    _entities.push_back(gui::Linemate({(float)value1, 0.05f, (float)value2}, 0.27f, BROWN));
        //if (isKayu == 3)
        //    _entities.push_back(gui::Deraumere({(float)value1, 0.05f, (float)value2}, 0.3f, BROWN));
        //if (isKayu == 4)
        //    _entities.push_back(gui::Phiras({(float)value1, 0.05f, (float)value2}, 0.3f, BROWN));
        //if (isKayu == 5)
        //    _entities.push_back(gui::Mendiane({(float)value1, 0.05f, (float)value2}, 0.3f, BROWN));
        //if (isKayu == 6)
        //    _entities.push_back(gui::Thystame({(float)value1, 0.05f, (float)value2}, 0.3f, BROWN));
        //if (isKayu == 7)
        //    _entities.push_back(gui::Sibur({(float)value1, 0.05f, (float)value2}, 0.7f, BROWN));
    }
    for (auto & entity : _entities) {
        Debug::InfoLog("Entity created: " + entity->getType() + " at position (" +
                       std::to_string(entity->getPosition().x) + ", " +
                       std::to_string(entity->getPosition().y) + ", " +
                       std::to_string(entity->getPosition().z) + ")");
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
    for (auto& entity : _entities) {
        Debug::InfoLog("Drawing entity: " + entity->getType() + " at position (" +
                       std::to_string(entity->getPosition().x) + ", " +
                       std::to_string(entity->getPosition().y) + ", " +
                       std::to_string(entity->getPosition().z) + ")");
        DrawModel(entity->getModel(), entity->getPosition(), entity->getScale(), entity->getColor());
    }
    for (auto& player : _players) {
        player.draw();
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
        player.update(_camera);
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
        player.drawUI();
        player.updateUI();
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

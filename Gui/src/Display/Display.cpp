/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Display
*/

#include "Menu.hpp"
#include "Client.hpp"
#include "Display.hpp"
#include "Settings.hpp"

#include "Logger.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Display::Display(std::shared_ptr<Camera> camera, std::shared_ptr<CamState> camState, std::shared_ptr<SceneState> sceneState, std::shared_ptr<int> timeUnit)
    : _camera(camera), _camState(camState), _sceneState(sceneState), _displayTeams(), _width(WIDTH), _height(HEIGHT)
gui::Display::Display(std::shared_ptr<Camera> camera, std::shared_ptr<CamState> camState, std::shared_ptr<SceneState> sceneState, std::function<void()> function)
    : _camera(camera), _camState(camState), _sceneState(sceneState), _width(WIDTH), _height(HEIGHT)
{

    _model = std::make_shared<Model>(LoadModel("assets/player/scene.glb"));
    _deadModel = LoadModel("assets/dead/scene.gltf");
    _animations = LoadModelAnimations("assets/player/scene.glb", &_animCount);
    _eggModel = std::make_shared<Model>(LoadModel("assets/egg/scene.gltf"));

    _timeUnit = timeUnit;
    _models = std::make_shared<std::vector<std::shared_ptr<Model>>>();
    _models->emplace_back(std::make_shared<Model>(LoadModel("assets/food/scene.gltf")));
    _models->emplace_back(std::make_shared<Model>(LoadModel("assets/linemate/scene.gltf")));
    _models->emplace_back(std::make_shared<Model>(LoadModel("assets/deraumere/scene.gltf")));
    _models->emplace_back(std::make_shared<Model>(LoadModel("assets/sibur/scene.gltf")));
    _models->emplace_back(std::make_shared<Model>(LoadModel("assets/mendiane/scene.gltf")));
    _models->emplace_back(std::make_shared<Model>(LoadModel("assets/phiras/scene.gltf")));
    _models->emplace_back(std::make_shared<Model>(LoadModel("assets/thystame/scene.gltf")));
    
    _map = std::make_shared<std::vector<std::shared_ptr<gui::Tile>>>();
    _eggs = std::make_shared<std::vector<std::shared_ptr<gui::Egg>>>();
    _players = std::make_shared<std::vector<std::shared_ptr<gui::Player>>>();
    _itemDisplay = {1, 1, 1, 1, 1, 1, 1};

    _menu = std::make_unique<gui::ui::Menu>(_sceneState, function);
    _settings = std::make_unique<gui::ui::Settings>(_sceneState);
    _menu->initMenuUI();
    _settings->initSettingsUI();
}

gui::Display::~Display()
{
}

/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/


void gui::Display::endGameUI()
{
    DrawRectangle(0, 0, 100, 50, LIGHTGRAY);
    DrawText("Game Over", 0, 0, 40, RED);
}

void gui::Display::endGame()
{

}

void gui::Display::displayEntity()
{
    for (int i = 0; i < static_cast<int>(_map->size()); ++i) {
        _map->operator[](i)->displayTile(_itemDisplay);
    }
    for (int i = 0; i < static_cast<int>(_players->size()); ++i) {
        _players->operator[](i)->draw();
        if (_players->operator[](i)->getCountBeforeExpire() == 0)
            _players->erase(_players->begin() + i);
    }
    for (int i = 0; i < static_cast<int>(_eggs->size()); ++i) {
        _eggs->operator[](i)->draw();
    }
}

void gui::Display::initOrbitalCamera(const Vector3& target, float distance)
{
    float theta = 45.0f * DEG2RAD;
    float phi = 30.0f * DEG2RAD;

    _camera->target = target;
    _camera->position = {
        target.x + distance * cosf(phi) * cosf(theta),
        target.y + distance * sinf(phi),
        target.z + distance * cosf(phi) * sinf(theta)
    };
    _camera->up = {0.0f, 1.0f, 0.0f};
    _camera->fovy = 45.0f;
    _camera->projection = CAMERA_PERSPECTIVE;
}

void gui::Display::updateCamera()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (*_camState == CamState::WORLD) {
            *_sceneState = SceneState::MENU;
        }
        else if (*_camState == CamState::PLAYER) {
            *_camera = { { -_width, 10.0f, -_height}, 
                        { _width / 2, 0.0f, _height / 2 }, 
                        { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
            *_camState = CamState::WORLD;
        }
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        if (*_camState == CamState::WORLD) {
            UpdateCamera(_camera.get(), CAMERA_THIRD_PERSON);
        }
        else if (*_camState == CamState::PLAYER) {
            for (auto& player : *_players) {
                if (player->getSelected() && !player->getIsMoving()) {
                    UpdateCamera(_camera.get(), CAMERA_ORBITAL);
                }
            }
        }
    }
    if (*_camState == CamState::PLAYER) {
        for (auto& player : *_players) {
            if (player->getSelected()) {
                if (player->getIsMoving()) {
                    _camera->target = player->getPosition();
                    _camera->position = {
                        player->getPosition().x - 2.0f,
                        player->getPosition().y + 2.0f,
                        player->getPosition().z - 2.0f
                    };
                }
            }
        }
    }
}

void gui::Display::handleInput()
{
    eventToggleDisplay();
    updateCamera();

    for (auto& tile: *_map)
        tile->handleUserInput(*_camera);
    for (auto& player : *_players) {
        if (player->update(*_camera) == 1) {
            for (auto& p : *_players) {
                if (p->getId() != player->getId() && p->getSelected()) {
                    player->setSelected(false);
                }
            }
        }
    }
    if (IsKeyPressed(KEY_P))
        _displayTeams->toggleDisplay();
}

void gui::Display::teamsDisplay()
{
    if (_displayTeams && !_displayTeams->getStatus())
        _displayTeams->display(std::pair<int, int>(-1, -1));
}

void gui::Display::render()
{
    BeginDrawing();

    if (_camera->position.y < 0.1f) {
        _camera->position.y = 0.1f;
    }
    ClearBackground({5, 5, 20, 255});
    BeginMode3D(*_camera);
    displayEntity();
    EndMode3D();
    for (auto& player : *_players) {
        player->drawUI();
        player->updateUI();
    }
    for (auto& tile: *_map) {
        tile->displayContent();
    }
    teamsDisplay();
    if (_winner)
        endGameUI();
    EndDrawing();
}

void gui::Display::eventToggleDisplay()
{
    if (IsKeyPressed(KEY_X)) {
        _winner = true;
        if (_displayTeams && _displayTeams->getStatus())
            _displayTeams->disableIsTile();
        _winnerTeam = "caca pipi";
    }
    if (IsKeyPressed(KEY_ONE)) {
        _itemDisplay[gui::Tile::FOOD] = (_itemDisplay[gui::Tile::FOOD] == 0) ? 1 : 0;
    }
    if (IsKeyPressed(KEY_TWO)) {
        _itemDisplay[gui::Tile::LINEMATE] = (_itemDisplay[gui::Tile::LINEMATE] == 0) ? 1 : 0;
    }
    if (IsKeyPressed(KEY_THREE)) {
        _itemDisplay[gui::Tile::DERAUMERE] = (_itemDisplay[gui::Tile::DERAUMERE] == 0) ? 1 : 0;
    }
    if (IsKeyPressed(KEY_FOUR)) {
        _itemDisplay[gui::Tile::SIBUR] = (_itemDisplay[gui::Tile::SIBUR] == 0) ? 1 : 0;
    }
    if (IsKeyPressed(KEY_FIVE)) {
        _itemDisplay[gui::Tile::MENDIANE] = (_itemDisplay[gui::Tile::MENDIANE] == 0) ? 1 : 0;
    }
    if (IsKeyPressed(KEY_SIX)) {
        _itemDisplay[gui::Tile::PHIRAS] = (_itemDisplay[gui::Tile::PHIRAS] == 0) ? 1 : 0;
    }
    if (IsKeyPressed(KEY_SEVEN)) {
        _itemDisplay[gui::Tile::THYSTAME] = (_itemDisplay[gui::Tile::THYSTAME] == 0) ? 1 : 0;
    }
}

std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> gui::Display::getMap()
{
    return _map;
}

std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> gui::Display::getEggs()
{
    return _eggs;
}

std::shared_ptr<std::vector<std::shared_ptr<Model>>> gui::Display::getModels()
{
    return _models;
}

std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> gui::Display::getPlayers()
{
    return _players;
}

void gui::Display::setTeams(std::shared_ptr<std::vector<std::string>> teams)
{
    _teams = std::move(teams);
}

void gui::Display::setTeamsColors(std::shared_ptr<std::map<std::string, Color>> teamColors)
{
    _teamColors = std::move(teamColors);
}

void gui::Display::setDisplayTeams(std::shared_ptr<TeamsDisplay> displayTeams)
{
    _displayTeams = std::move(displayTeams);
}

void gui::Display::setWinner(const std::string& team)
{
    _winner = true;
    _winnerTeam = team;
}


void gui::Display::addPlayer(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team)
{
    _players->emplace_back(std::make_shared<gui::Player>(id, position, orientation, level, team, 0.35, SCREEN_WIDTH, SCREEN_HEIGHT,
        *_camera, *_camState, _timeUnit, _model, _deadModel, _animations, _animCount, _models->at(4)));
}

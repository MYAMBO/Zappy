/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/

#include <thread>

#include "Scene.hpp"
#include "Menu.hpp"
#include "Client.hpp"
#include "Settings.hpp"
#include "Logger.hpp"

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/

gui::Scene::Scene(const std::string& hostname, const std::string& port)
    : _isOpen(true)
{
    Debug::InfoLog("Zappy started");
    _camera = std::make_shared<Camera>();
    _camState = std::make_shared<CamState>(CamState::WORLD);
    _currentState = std::make_shared<SceneState>(SceneState::MENU);
    std::shared_ptr<std::string> sharedHostname = std::make_shared<std::string>(hostname);
    std::shared_ptr<std::string> sharedPort = std::make_shared<std::string>(port);
    initWindow();

    _timeUnit = std::make_shared<int>(100);
    _display = std::make_unique<Display>(_camera, _camState, _currentState, _timeUnit);
    _client = std::make_shared<gui::Client>(_display->getPlayers(), _display->getMap(), _display->getEggs(), _camera, _camState, _display->getModels(), _display, _timeUnit);
    _display = std::make_shared<Display>(_camera, _camState, _currentState, _client->connectToServer());

    _display->_menu->setHostname(sharedHostname);
    _display->_menu->setPort(sharedPort);

    _client = std::make_shared<gui::Client>(_display->getPlayers(), _display->getMap(), _display->getEggs(), _camera, _camState, _display->getModels(), _display, sharedHostname, sharedPort);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    _client->sendCommand("sgt");
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

    ToggleFullscreen();

    _camera->position = { -WIDTH, 10.0f, -HEIGHT };
    _camera->target = { WIDTH / 2, 0.0f, HEIGHT / 2 };
    _camera->up = { 0.0f, 1.0f, 0.0f };
    _camera->fovy = 45.0f;
    _camera->projection = CAMERA_PERSPECTIVE;
}

bool gui::Scene::isOpen() const
{
    return _isOpen;
}

void gui::Scene::handleStateLogic()
{
    switch (*_currentState) {
        case SceneState::GAME:
            _display->handleInput();
            _display->render();
            break;
            
        case SceneState::EXIT:
            Debug::InfoLog("[GUI] Exit state reached, closing window");
            _isOpen = false;
            break;
            
        case SceneState::MENU:
            _display->_menu->handleMenuInput();
            _display->_menu->drawMainMenu();
            break;
            
        case SceneState::SETTINGS:
            _display->_settings->handleSettingsInputs();
            _display->_settings->drawSettings();
            break;
    }
}

void gui::Scene::update()
{
    if (!_isOpen) {
        return;
    }
    
    handleStateLogic();
}
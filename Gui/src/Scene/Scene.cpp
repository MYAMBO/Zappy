/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/

#include <thread>
#include <chrono>

#include "Menu.hpp"
#include "Scene.hpp"
#include "Client.hpp"
#include "Settings.hpp"

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

    _display = std::make_shared<Display>(_camera, _camState, _currentState);

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

    _camera->position = { -WIDTH, 10.0f, -HEIGHT };
    _camera->target = { WIDTH / 2, 0.0f, HEIGHT / 2 };
    _camera->up = { 0.0f, 1.0f, 0.0f };
    _camera->fovy = 45.0f;
    _camera->projection = CAMERA_PERSPECTIVE;
}

std::shared_ptr<Model> gui::Scene::safeModelLoader(const std::string& path)
{
    std::cout << path << std::endl;
    std::shared_ptr<Model> model = std::make_shared<Model>(LoadModel(path.c_str()));

    if (model->meshCount == 0 || model->meshes == nullptr)
        throw gui::FailedLoadModel();

    return model;
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
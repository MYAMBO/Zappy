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
    : _camState(CamState::WORLD), _isOpen(true), _width(WIDTH), _height(HEIGHT), _currentState(SceneState::GAME), _models() //don't forget here
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

    this->_menu = std::make_unique<gui::ui::Menu>(this->_currentState, SCREEN_WIDTH, SCREEN_HEIGHT);
    this->_itemDisplay = {1, 1, 1, 1, 1, 1, 1};
    this->_menu->initMenuUI();
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

    this->_camera = { { -_width, 10.0f, -_height}, { _width / 2, 0.0f, _height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
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

            this->_map.emplace_back(std::make_shared<gui::Tile>(coord, qty, this->_models)); // remove model here
        }
    }
    for (int x = 0; (float)x < 10; ++x) {
        std::pair<int, int> coord = {GetRandomValue(0, (int)WIDTH - 1), GetRandomValue(0, (int)HEIGHT - 1)};
        this->_players.emplace_back(std::make_shared<gui::Player>(x, coord, North, 1, "toto", 1, SCREEN_WIDTH, SCREEN_HEIGHT, this->_camera, this->_camState));
    }
}

void gui::Scene::displayEntity()
{
    for (auto& tile : this->_map) {
        tile->displayTile(this->_itemDisplay);
    }
    for (auto& player : this->_players) {
        player->draw();
    }
}

void gui::Scene::handleInput()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (this->_camState == CamState::WORLD) {
            this->_currentState = SceneState::MENU;
        }
        else if (this->_camState == CamState::PLAYER) {
            this->_camState = CamState::WORLD;
        }
    }
    for (auto& player : this->_players)
        player->update(this->_camera);
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        if (this->_camState == CamState::WORLD) {
            UpdateCamera(&this->_camera, CAMERA_THIRD_PERSON);
        }
        else if (this->_camState == CamState::PLAYER) {
            UpdateCamera(&this->_camera, CAMERA_ORBITAL);
        }
    }
}

void gui::Scene::render()
{
    BeginDrawing();
    if (this->_camera.position.y < 0.1f) {
        this->_camera.position.y = 0.1f;
    }
    ClearBackground(BLACK);
    BeginMode3D(this->_camera);
    displayEntity();
    EndMode3D();
    for (auto& player : this->_players) {
        player->drawUI();
        player->updateUI();
    }
    EndDrawing();
}

bool gui::Scene::isOpen() const
{
    return this->_isOpen && !WindowShouldClose();
}

void gui::Scene::update()
{
    if (!this->_isOpen) {
        return;
    }

    switch (this->_currentState) {
        case SceneState::GAME:
            eventToggleDisplay();
            handleInput();
            render();
            break;
        case SceneState::EXIT:
            this->_isOpen = false;
            break;
        case SceneState::MENU:
            this->_menu->handleMenuInput();
            this->_menu->drawMainMenu();
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
        if (this->_itemDisplay[gui::Tile::FOOD] == 0) {
            this->_itemDisplay[gui::Tile::FOOD] = 1;
        } else {
            Debug::InfoLog("[GUI] Food display toggled");
            this->_itemDisplay[gui::Tile::FOOD] = 0;
        }
    }
    if (IsKeyPressed(KEY_TWO)) {
        if (this->_itemDisplay[gui::Tile::LINEMATE] == 0) {
            this->_itemDisplay[gui::Tile::LINEMATE] = 1;
        } else {
            this->_itemDisplay[gui::Tile::LINEMATE] = 0;
        }
    }
    if (IsKeyPressed(KEY_THREE)) {
        if (this->_itemDisplay[gui::Tile::DERAUMERE] == 0) {
            this->_itemDisplay[gui::Tile::DERAUMERE] = 1;
        } else {
            this->_itemDisplay[gui::Tile::DERAUMERE] = 0;
        }
    }
    if (IsKeyPressed(KEY_FOUR)) {
        if (this->_itemDisplay[gui::Tile::SIBUR] == 0) {
            this->_itemDisplay[gui::Tile::SIBUR] = 1;
        } else {
            this->_itemDisplay[gui::Tile::SIBUR] = 0;
        }
    }
    if (IsKeyPressed(KEY_FIVE)) {
        if (this->_itemDisplay[gui::Tile::MENDIANE] == 0) {
            this->_itemDisplay[gui::Tile::MENDIANE] = 1;
        } else {
            this->_itemDisplay[gui::Tile::MENDIANE] = 0;
        }
    }
    if (IsKeyPressed(KEY_SIX)) {
        if (this->_itemDisplay[gui::Tile::PHIRAS] == 0) {
            this->_itemDisplay[gui::Tile::PHIRAS] = 1;
        } else {
            this->_itemDisplay[gui::Tile::PHIRAS] = 0;
        }
    }
    if (IsKeyPressed(KEY_SEVEN)) {
        if (this->_itemDisplay[gui::Tile::THYSTAME] == 0) {
            this->_itemDisplay[gui::Tile::THYSTAME] = 1;
        } else {
            this->_itemDisplay[gui::Tile::THYSTAME] = 0;
        }
    }
}

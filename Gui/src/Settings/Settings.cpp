/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Settings
*/

#include "Logger.hpp"
#include "Settings.hpp"

gui::ui::Settings::Settings(std::shared_ptr<SceneState> sceneState)
    : _sceneState(sceneState), 
      _backButton([this]() { backButtonClicked(); }, Rectangle{static_cast<float>(SCREEN_WIDTH) * 0.01f, static_cast<float>(SCREEN_HEIGHT) * 0.01f, 200.0f, 100.0f}, "Back"),
      _screenWidth(SCREEN_WIDTH), _screenHeight(SCREEN_HEIGHT), _color(7), _box(7), _key(7), _name(7),
      _cameraKeys(10), _cameraActions(10)
{
    initSettingsUI();
    initResourceItems();
    initCameraControls();
}

gui::ui::Settings::~Settings() 
{
}

void gui::ui::Settings::initSettingsUI()
{
    _commandBox = Rectangle{static_cast<float>(_screenWidth) * 0.1f, static_cast<float>(_screenHeight) * 0.15f, static_cast<float>(_screenWidth) * 0.8f, static_cast<float>(_screenHeight) * 0.35f};
    _cameraBox = Rectangle{static_cast<float>(_screenWidth) * 0.1f, static_cast<float>(_screenHeight) * 0.55f, static_cast<float>(_screenWidth) * 0.8f, static_cast<float>(_screenHeight) * 0.35f};

    Debug::InfoLog("[GUI] Settings UI initialized");
}

void gui::ui::Settings::initResourceItems()
{
    Debug::InfoLog("[GUI] Initializing resource items");
    _key[0] = std::string("1");
    _key[1] = std::string("2");
    _key[2] = std::string("3");
    _key[3] = std::string("4");
    _key[4] = std::string("5");
    _key[5] = std::string("6");
    _key[6] = std::string("7");
    Debug::InfoLog("[GUI] Resource keys initialized");
    _color[0] = BROWN;
    _color[1] = YELLOW;
    _color[2] = GREEN;
    _color[3] = RED;
    _color[4] = WHITE;
    _color[5] = BLUE;
    _color[6] = PURPLE;
    Debug::InfoLog("[GUI] Resource colors initialized");
    _name[0] = std::string("Food");
    _name[1] = std::string("Sibur");
    _name[2] = std::string("Phiras");
    _name[3] = std::string("Linemate");
    _name[4] = std::string("Mendiane");
    _name[5] = std::string("Thystame");
    _name[6] = std::string("Deraumere");
    Debug::InfoLog("[GUI] Resource items initialized");
}

void gui::ui::Settings::initCameraControls()
{
    Debug::InfoLog("[GUI] Initializing camera controls");
    _cameraKeys[0] = std::string("Escape");
    _cameraKeys[1] = std::string("Crtl - ZQSD");
    _cameraKeys[2] = std::string("Crtl - Mouse");
    _cameraKeys[3] = std::string("Crtl - Scroll");
    _cameraKeys[4] = std::string("When On Player / Crtl");
    _cameraKeys[5] = std::string("When On Player / Escape");
    _cameraKeys[6] = std::string("Click on Player");
    _cameraKeys[7] = std::string("Shift - Click on Tiles");
    _cameraKeys[8] = std::string("P");
    _cameraKeys[9] = std::string("B");
    
    _cameraActions[0] = std::string("Exit Camera View");
    _cameraActions[1] = std::string("Move Camera (Forward/Back/Left/Right)");
    _cameraActions[2] = std::string("Look Around");
    _cameraActions[3] = std::string("Zoom In/Out");
    _cameraActions[4] = std::string("Turn Around Player");
    _cameraActions[5] = std::string("Exit Player View");
    _cameraActions[6] = std::string("Select Player");
    _cameraActions[7] = std::string("Select Tiles");
    _cameraActions[8] = std::string("Toggle Number of Players/Eggs");
    _cameraActions[9] = std::string("Toggle Broadcasting");
    Debug::InfoLog("[GUI] Camera controls initialized");
}

void gui::ui::Settings::handleSettingsInputs()
{
    _backButton.update();
    if (IsKeyPressed(KEY_ESCAPE)) {
        Debug::InfoLog("[GUI] Escape key pressed, returning to menu");
        *_sceneState = SceneState::MENU;
    }
}

void gui::ui::Settings::drawSettings()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawText("Settings", static_cast<int>(_screenWidth / 2 - 70), static_cast<int>(_screenHeight / 20), 40, WHITE);
    
    // Draw Resource Controls Section
    DrawRectangleRec(_commandBox, GRAY);
    DrawRectangleLinesEx(_commandBox, 2, WHITE);
    DrawText("Resource Toggle Controls", static_cast<int>(_commandBox.x + 10), static_cast<int>(_commandBox.y + 10), 24, WHITE);
    int yOffset = 50;
    for (int i = 0; i < 7; i++) {
        _box[i] = Rectangle{_commandBox.x + 20, _commandBox.y + yOffset, 20, 20};
        DrawRectangleRec(_box[i], _color[i]);
        DrawText(_key[i].c_str(), 
                static_cast<int>(_commandBox.x + 50), 
                static_cast<int>(_commandBox.y + yOffset), 20, WHITE);
        DrawText((" :  Toggle " + _name[i]).c_str(), 
                static_cast<int>(_commandBox.x + 100), 
                static_cast<int>(_commandBox.y + yOffset), 20, WHITE);
        yOffset += 30;
    }
    
    // Draw Camera Controls Section
    DrawRectangleRec(_cameraBox, GRAY);
    DrawRectangleLinesEx(_cameraBox, 2, WHITE);
    DrawText("Camera Controls", static_cast<int>(_cameraBox.x + 10), static_cast<int>(_cameraBox.y + 10), 24, WHITE);
    yOffset = 50;
    for (size_t i = 0; i < _cameraKeys.size(); i++) {
        Debug::InfoLog("[GUI] Drawing camera control: " + _cameraKeys[i]);
        DrawText(_cameraKeys[i].c_str(), 
                static_cast<int>(_cameraBox.x + 20), 
                static_cast<int>(_cameraBox.y + yOffset), 20, WHITE);
        DrawText((" :  " + _cameraActions[i]).c_str(), 
                static_cast<int>(_cameraBox.x + 300), 
                static_cast<int>(_cameraBox.y + yOffset), 20, WHITE);
        yOffset += 25;
    }
    
    _backButton.draw();
    EndDrawing();
}

void gui::ui::Settings::backButtonClicked()
{
    *_sceneState = SceneState::MENU;
    Debug::InfoLog("[GUI] Back button clicked in settings");
}
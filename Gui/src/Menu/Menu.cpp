/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Logger.hpp"

gui::ui::Menu::Menu(SceneState &SceneState, int screenWidth, int screenHeight)
    :   _sceneState(SceneState),
        _playButton([this]() { playClicked(); }, Rectangle{static_cast<float>(screenWidth) / 2 - 100, static_cast<float>(screenHeight) / 2.6f - 200, 200.0f, 100.0f}, "Play"),
        _exitButton([this]() { closeWindow(); }, Rectangle{static_cast<float>(screenWidth) / 2 - 100, static_cast<float>(screenHeight) / 1.5f - 200, 200.0f, 100.0f}, "Exit"),
        _settingButton([this]() { settingClicked(); }, Rectangle{static_cast<float>(screenWidth) / 2 - 100, static_cast<float>(screenHeight) / 1.9f - 200, 200.0f, 100.0f}, "Settings"),
        _screenWidth(screenWidth), _screenHeight(screenHeight)
{
    Debug::InfoLog("[GUI] Menu initialized");
}

gui::ui::Menu::~Menu()
{
}


void gui::ui::Menu::initMenuUI()
{
    Debug::InfoLog("[GUI] Initializing menu UI elements");
    _frameCounter = 0;
    _serverIdActive = false;
    _serverId.clear();

    _serverIdBox = Rectangle{static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - 200, 660.0f, 30.0f};

    _inputBoxColor = LIGHTGRAY;
    _backgroundColor = DARKGRAY;
    _inputBoxActiveColor = SKYBLUE;

    _titleFontSize = 40;
    _inputFontSize = 20;
    _buttonFontSize = 20;
}

void gui::ui::Menu::playClicked()
{
    if (_serverId.length() > 0) {
        // call func for try connecting to server 
        // if (connection good)
        _sceneState = SceneState::GAME;
        _serverIdActive = false;
        Debug::InfoLog("[GUI] Play button clicked, connecting to server with ID: " + _serverId);
    } else {
        _errorInput = 60;
    }
}

void gui::ui::Menu::closeWindow()
{
    _sceneState = SceneState::EXIT;
    Debug::InfoLog("[GUI] Exit button clicked, closing window");
}

void gui::ui::Menu::settingClicked()
{
    _sceneState = SceneState::SETTINGS;
    Debug::InfoLog("[GUI] Settings button clicked");
}

void gui::ui::Menu::handleMenuInput()
{
    _playButton.update();
    _exitButton.update();
    _settingButton.update();
    if (IsKeyPressed(KEY_ENTER)) {
        playClicked();
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        Debug::InfoLog("[GUI] Escape key pressed, closing window");
        closeWindow();
    }
    handleTextInput();
}


void gui::ui::Menu::handleTextInput()
{
    if (IsKeyPressed(KEY_BACKSPACE) && _serverIdActive && !_serverId.empty()) {
        _serverId.pop_back();
    }

    if (_serverIdActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {
                if (_serverId.length() < MAX_SERVER_ID_LENGTH) {
                    _serverId += (char)key;
                    Debug::InfoLog("[GUI] Char pressed: " + std::string(1, (char)key));
                }
            }
            key = GetCharPressed();
        }
    }
    if (IsKeyPressed(KEY_TAB) || (_serverIdBox.x <= GetMouseX() && GetMouseX() <= _serverIdBox.x + _serverIdBox.width &&
        _serverIdBox.y <= GetMouseY() && GetMouseY() <= _serverIdBox.y + _serverIdBox.height && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
        _serverIdActive = !_serverIdActive;
    }
}

void gui::ui::Menu::drawMainMenu()
{
    BeginDrawing();
    ClearBackground(_backgroundColor);
    DrawText("Zappy", static_cast<float>(_screenWidth) / 2 - 70, static_cast<float>(_screenHeight / 10), _titleFontSize, WHITE);

    _playButton.draw();
    _exitButton.draw();
    _settingButton.draw();

    if (_errorInput > 0)
        DrawText("Server ID is required!", static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - 220, _inputFontSize, WHITE);
    if (_serverIdActive) {
        if (_errorInput > 0) {
            _errorInput--;
            DrawRectangleRec(_serverIdBox, RED);
        } else {
            DrawRectangleRec(_serverIdBox, _inputBoxActiveColor);
            DrawText("Server ID:", static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - 220, _inputFontSize, WHITE);
        }
    } else {
        if (_errorInput > 0) {
            _errorInput--;
            DrawRectangleRec(_serverIdBox, RED);
        } else {
            DrawRectangleRec(_serverIdBox, _inputBoxColor);
            DrawText("Server ID:", static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - 220, _inputFontSize, WHITE);
        }
    }

    DrawText(_serverId.c_str(), _serverIdBox.x + 10, _serverIdBox.y + 10, _inputFontSize, BLACK);
    EndDrawing();
}

void gui::ui::Menu::drawConnectingScreen()
{
    ClearBackground(_backgroundColor);
    DrawText("Connecting to server...", 100, 50, _titleFontSize, WHITE);
    DrawText(_serverId.c_str(), 100, 150, _inputFontSize, BLACK);
}
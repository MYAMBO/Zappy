/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Menu
*/

#include "Menu.hpp"

#include <utility>
#include "Logger.hpp"

gui::ui::Menu::Menu(std::shared_ptr<SceneState> SceneState)
    :   _connectionFunction(), _sceneState(std::move(SceneState)),
        _playButton([this]() { playClicked(); }, Rectangle{static_cast<float>(SCREEN_WIDTH) / 2 - 100, static_cast<float>(SCREEN_HEIGHT) / 2.6f - 200, 200.0f, 100.0f}, "Play"),
        _exitButton([this]() { closeWindow(); }, Rectangle{static_cast<float>(SCREEN_WIDTH) / 2 - 100, static_cast<float>(SCREEN_HEIGHT) / 1.5f - 200, 200.0f, 100.0f}, "Exit"),
        _settingButton([this]() { settingClicked(); }, Rectangle{static_cast<float>(SCREEN_WIDTH) / 2 - 100, static_cast<float>(SCREEN_HEIGHT) / 1.9f - 200, 200.0f, 100.0f}, "Settings"),
        _screenWidth(SCREEN_WIDTH), _screenHeight(SCREEN_HEIGHT)
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
    _hostnameActive = false;
    _portActive = false;

    _hostnameBox = Rectangle{static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - 200, 660.0f, 30.0f};
    _portBox = Rectangle{static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - 100, 660.0f, 30.0f};

    _inputBoxColor = LIGHTGRAY;
    _backgroundColor = DARKGRAY;
    _inputBoxActiveColor = SKYBLUE;

    _hostnameError = 0;
    _portError = 0;
    _titleFontSize = 40;
    _inputFontSize = 20;
    _buttonFontSize = 20;
}

void gui::ui::Menu::playClicked()
{
    if (_hostname->empty())
        _hostnameError = 60;

    if (_port->empty())
        _portError = 60;

    if (!_hostname->empty() && !_port->empty()) {
        *_sceneState = SceneState::GAME;
        _hostnameActive = false;
        _portActive = false;
        _connectionFunction();
        Debug::InfoLog("[GUI] Play button clicked, connecting to server with Hostname: " + *_hostname);
        Debug::InfoLog("[GUI] Play button clicked, connecting to server with Port: " + *_port);
    }
}

void gui::ui::Menu::closeWindow()
{
    *_sceneState = SceneState::EXIT;
    Debug::InfoLog("[GUI] Exit button clicked, closing window");
}

void gui::ui::Menu::settingClicked()
{
    *_sceneState = SceneState::SETTINGS;
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
    if (_hostnameActive) {
        if (IsKeyPressed(KEY_BACKSPACE) && !_hostname->empty()) {
            if (IsKeyDown(KEY_LEFT_CONTROL))
                _hostname->clear();
            else
                _hostname->pop_back();
        }

        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {
                if (_hostname->length() < MAX_SERVER_ID_LENGTH) {
                    _hostname->push_back((char)key);
                    Debug::InfoLog("[GUI] Char pressed: " + std::string(1, (char)key));
                }
            }
            key = GetCharPressed();
        }
    }

    if (_portActive) {
        if (IsKeyPressed(KEY_BACKSPACE) && !_port->empty()) {
            if (IsKeyDown(KEY_LEFT_CONTROL))
                _port->clear();
            else
                _port->pop_back();
        }

        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {
                if (_port->length() < MAX_SERVER_ID_LENGTH) {
                    _port->push_back((char)key);
                    Debug::InfoLog("[GUI] Char pressed: " + std::string(1, (char)key));
                }
            }
            key = GetCharPressed();
        }
    }

    if ((IsKeyPressed(KEY_TAB) && _hostnameActive) ||
        (_portBox.x <= GetMouseX() && GetMouseX() <= _portBox.x + _portBox.width &&
         _portBox.y <= GetMouseY() && GetMouseY() <= _portBox.y + _portBox.height && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
        if (_hostnameActive)
            _hostnameActive = false;
        _portActive = true;
        return;
    }

    if ((IsKeyPressed(KEY_TAB) && !_hostnameActive) ||
        (_hostnameBox.x <= GetMouseX() && GetMouseX() <= _hostnameBox.x + _hostnameBox.width &&
         _hostnameBox.y <= GetMouseY() && GetMouseY() <= _hostnameBox.y + _hostnameBox.height && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
        if (_portActive)
            _portActive = false;
        _hostnameActive = true;
        return;
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

    drawTextBox(_hostnameError, _hostnameActive, _hostnameBox, 220, "Hostname :", "Hostname is required!");
    drawTextBox(_portError, _portActive, _portBox, 120, "Port :", "Port is required!");

    DrawText(_hostname->c_str(), static_cast<int>(_hostnameBox.x) + 10, static_cast<int>(_hostnameBox.y) + 10, _inputFontSize, BLACK);
    DrawText(_port->c_str(), static_cast<int>(_portBox.x) + 10, static_cast<int>(_portBox.y) + 10, _inputFontSize, BLACK);
    EndDrawing();
}

void gui::ui::Menu::drawTextBox(int errorNb, bool active, Rectangle box, int height, const std::string& name, const std::string& errorStr)
{
    if (errorNb > 0)
        DrawText(errorStr.c_str(), static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - static_cast<float>(height), _inputFontSize, WHITE);
    if (active) {
        if (errorNb > 0) {
            errorNb--;
            DrawRectangleRec(box, RED);
        } else {
            DrawRectangleRec(box, _inputBoxActiveColor);
            DrawText(name.c_str(), static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - static_cast<float>(height), _inputFontSize, WHITE);
        }
    } else {
        if (errorNb > 0) {
            errorNb--;
            DrawRectangleRec(box, RED);
        } else {
            DrawRectangleRec(box, _inputBoxColor);
            DrawText(name.c_str(), static_cast<float>(_screenWidth) / 2 - 330, static_cast<float>(_screenHeight) / 1.2f - static_cast<float>(height), _inputFontSize, WHITE);
        }
    }
}

void gui::ui::Menu::drawConnectingScreen()
{
    ClearBackground(_backgroundColor);
    DrawText("Connecting to server...", 100, 50, _titleFontSize, WHITE);
    DrawText(_hostname->c_str(), 100, 150, _inputFontSize, BLACK);
}

/************************************************************
**         >>>>      SETTERS / GETTERS        <<<<         **
************************************************************/

void gui::ui::Menu::setHostname(std::shared_ptr<std::string> name)
{
    this->_hostname = std::move(name);
}

void gui::ui::Menu::setPort(std::shared_ptr<std::string> name)
{
    this->_port = std::move(name);
}

void gui::ui::Menu::setFunction(std::function<void ()> function)
{
    _connectionFunction = function;
}

std::shared_ptr<std::string> gui::ui::Menu::getHostname()
{
    return this->_hostname;
}

std::shared_ptr<std::string> gui::ui::Menu::getPort()
{
    return this->_port;
}

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

    _menu = std::make_unique<gui::ui::Menu>(_sceneState);
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


void gui::Display::drawOverlay(Color color)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);
}

Rectangle gui::Display::drawCenteredPanel(int width, int height, Color bgColor)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int panelX = (screenWidth - width) / 2;
    int panelY = (screenHeight - height) / 2;
    
    Rectangle panel = {(float)panelX, (float)panelY, (float)width, (float)height};
    
    DrawRectangleRounded(panel, 0.1f, 10, bgColor);
    DrawRectangleRoundedLines(panel, 0.1f, 10, bgColor);
    
    return panel;
}

void gui::Display::drawTextWithShadow(std::string text, Vector2 position, float fontSize, Color textColor, Color shadowColor,  Vector2 shadowOffset)
{
    Vector2 shadowPos = {position.x + shadowOffset.x, position.y + shadowOffset.y};
    DrawTextEx(GetFontDefault(), text.c_str(), shadowPos, fontSize, 2.0f, shadowColor);
    DrawTextEx(GetFontDefault(), text.c_str(), position, fontSize, 2.0f, textColor);
}

void gui::Display::drawPulsingText(std::string text, Rectangle container, float fontSize, Color color, float pulseSpeed, float pulseAmount)
{
    static float pulseTimer = 0.0f;
    pulseTimer += GetFrameTime();
    float pulseScale = 1.0f + pulseAmount * sinf(pulseTimer * pulseSpeed);
    
    int textWidth = MeasureText(text.c_str(), (int)(fontSize * pulseScale));
    float textX = container.x + (container.width - textWidth) / 2;
    float textY = container.y + (container.height - fontSize * pulseScale) / 2;
    
    drawTextWithShadow(text, {textX, textY}, fontSize * pulseScale, color, BLACK, {2.0f, 2.0f});
}

Vector2 gui::Display::drawCenteredText(std::string text, float y, float fontSize, Color color, Rectangle container)
{
    int textWidth = MeasureText(text.c_str(), (int)fontSize);
    float textX = container.x + (container.width - textWidth) / 2;
    Vector2 position = {textX, y};
    
    DrawTextEx(GetFontDefault(), text.c_str(), position, fontSize, 1.0f, color);
    return position;
}

void gui::Display::drawSeparatorLine(Rectangle container, float yOffset, Color color, float thickness)
{
    float lineY = container.y + yOffset;
    float margin = 50.0f;
    DrawLineEx({container.x + margin, lineY}, {container.x + container.width - margin, lineY}, thickness, color);
}

bool gui::Display::drawButton(Rectangle bounds, std::string text, Color normalColor, Color hoverColor, Color textColor)
{
    Vector2 mousePos = GetMousePosition();
    bool isHovered = CheckCollisionPointRec(mousePos, bounds);
    bool isClicked = false;
    
    Color buttonColor = isHovered ? hoverColor : normalColor;
    DrawRectangleRounded(bounds, 0.1f, 10, buttonColor);
    DrawRectangleRoundedLines(bounds, 0.1f, 10, WHITE);
    
    int textWidth = MeasureText(text.c_str(), 20);
    float textX = bounds.x + (bounds.width - textWidth) / 2;
    float textY = bounds.y + (bounds.height - 20) / 2;
    
    DrawText(text.c_str(), (int)textX, (int)textY, 20, textColor);
    
    if (isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isClicked = true;
    }
    
    return isClicked;
}

float gui::Display::fadeInAnimation(float duration, bool reset)
{
    static float timer = 0.0f;
    if (reset) timer = 0.0f;
    
    timer += GetFrameTime();
    return fminf(timer / duration, 1.0f);
}

Color gui::Display::glowEffect(Color baseColor, float speed, float intensity)
{
    static float glowTimer = 0.0f;
    glowTimer += GetFrameTime();
    
    float glow = (1.0f + intensity * sinf(glowTimer * speed)) / (1.0f + intensity);
    
    return {
        (unsigned char)(baseColor.r * glow),
        (unsigned char)(baseColor.g * glow),
        (unsigned char)(baseColor.b * glow),
        baseColor.a
    };
}

std::string gui::Display::typingEffect(std::string fullText, float speed, bool reset)
{
    static float timer = 0.0f;
    static int currentLength = 0;
    
    if (reset) {
        timer = 0.0f;
        currentLength = 0;
    }
    
    timer += GetFrameTime();
    int targetLength = (int)(timer * speed);
    int fullLength = (int)fullText.length();
    
    currentLength = fminf(targetLength, fullLength);
    
    return std::string(fullText, currentLength);
}

void gui::Display::drawNotification(std::string message, float duration, Color bgColor, bool reset)
{
    static float timer = 0.0f;
    static bool show = true;
    
    if (reset) {
        timer = 0.0f;
        show = true;
    }
    
    if (!show) return;
    
    timer += GetFrameTime();
    if (timer > duration) {
        show = false;
        return;
    }
    
    float alpha = 1.0f;
    if (timer > duration - 1.0f) {
        alpha = duration - timer;
    }
    
    int width = 300;
    int height = 60;
    int x = GetScreenWidth() - width - 20;
    int y = 20;
    
    bgColor.a = (unsigned char)(bgColor.a * alpha);
    DrawRectangleRounded({(float)x, (float)y, (float)width, (float)height}, 0.1f, 10, bgColor);
    
    Color textColor = WHITE;
    textColor.a = (unsigned char)(255 * alpha);
    drawCenteredText(message, y + 20, 18, textColor, {(float)x, (float)y, (float)width, (float)height});
}


void gui::Display::endGameUI()
{
    drawOverlay();

    Rectangle panel = drawCenteredPanel(600, 400, DARKGRAY);   
    Rectangle titleArea = {panel.x, panel.y + 20, panel.width, 80};

    drawPulsingText("GAME OVER", titleArea, 48, RED, 0.5f, 0.1f);
    drawSeparatorLine(panel, 140, LIGHTGRAY, 2.0f);
    drawCenteredText("WINNER", panel.y + 180, 24, LIGHTGRAY, panel);
    
    Color teamColor = GOLD;
    if (_teamColors && _teamColors->find(_winnerTeam) != _teamColors->end()) {
        teamColor = _teamColors->at(_winnerTeam);
    }
    teamColor = glowEffect(teamColor, 0.5f, 0.2f);
    drawTextWithShadow(_winnerTeam.c_str(), {panel.x + (panel.width - MeasureText(_winnerTeam.c_str(), 36)) / 2, panel.y + 220}, 36, teamColor, BLACK, {2.0f, 2.0f});
    drawCenteredText("Press ESC to main menu", panel.y + panel.height - 55, 18, LIGHTGRAY, panel);

    if (IsKeyPressed(KEY_SPACE)) {
        _winner = false;
        _winnerTeam = "";
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        *_sceneState = SceneState::MENU;
        _winner = false;
        _winnerTeam = "";
    }
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

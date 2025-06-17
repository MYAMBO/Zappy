/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include "Food.hpp"
#include "Sibur.hpp"
#include "AItem.hpp"
#include "Button.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Phiras.hpp"
#include "Linemate.hpp"
#include "Mendiane.hpp"
#include "Thystame.hpp"
#include "Inventory.hpp"
#include "Deraumere.hpp"
#include "Tile.hpp"

#include <iostream>
#include <memory>

void displayMap(const std::vector<std::shared_ptr<gui::Tile>>& map)
{
    for (const auto& tile: map) {
        tile->displayTile();
    }
}

void displayPlayer(const std::vector<std::shared_ptr<gui::Player>>& list)
{
    for (auto & i : list) {
        DrawModel(i->getModel(), i->getPosition(), i->getScale(), i->getColor());
    }
}

void displayPlayerUi(const std::vector<std::shared_ptr<gui::Player>>& list)
{
    for (auto & i : list) {
        i->updateUI();
        i->drawUI();
    }
}

#define WIDTH 10
#define HEIGHT 10

int main()
{
    //--------------------------------------------------------- Temp brut code ----------------------------------------------------------------
    float width = WIDTH;
    float height = HEIGHT;

    //--------------------------------------------------------- Init ----------------------------------------------------------------
    Debug::ClearLogFile();
    Debug::InfoLog("Zappy started");
    // ------ Window ------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Zappy");
    SetTargetFPS(60);

    // ------ Brut code for Entity on Map ------
    std::vector<std::shared_ptr<gui::Player>> list;
    Camera camera = { { -width, 10.0f, -height}, { width / 2, 0.0f, height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    int sceneState = 1;

    std::vector<std::shared_ptr<gui::Tile>> Map;

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

            Map.emplace_back(std::make_shared<gui::Tile>(coord, food, linemate, deraumere, sibur, mendiane, phiras, thystame));
        }
    }

    for (int x = 0; (float)x < 10; ++x) {
        std::pair<int, int> coord = {GetRandomValue(0, (int)width - 1), GetRandomValue(0, (int)height - 1)};

        list.emplace_back(std::make_shared<gui::Player>(x, coord, North, 1, "toto", 1, screenWidth, screenHeight, camera, sceneState));
    }

    //--------------------------------------------------------- Display ----------------------------------------------------------------

    while (sceneState != 0) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            sceneState--;
            if (sceneState == 1)
                camera = { { -width, 10.0f, -height}, { width / 2, 0.0f, height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
        }
        for (auto & i : list)
            i->update(camera);
        if (IsKeyDown(KEY_LEFT_CONTROL) && sceneState == 1)
            UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        else if (IsKeyDown(KEY_LEFT_CONTROL) && sceneState == 2)
            UpdateCamera(&camera, CAMERA_ORBITAL);
        BeginDrawing();
        if (camera.position.y < 0.1)
            camera.position.y = 0.1;
        ClearBackground(BLACK);
        BeginMode3D(camera);
        displayMap(Map);
        displayPlayer(list);
        EndMode3D();
        for (auto & i : list) {
            i->updateUI();
            i->drawUI();
        }
        EndDrawing();
    }
    list.clear();
    CloseWindow();

    return 0;
}
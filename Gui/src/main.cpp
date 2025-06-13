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

#include <iostream>

#define WIDTH 10
#define HEIGHT 10


void displayMap(float width, float height)
{
    for (int x = 0; (float)x < width; x++) {
        for (int z = 0; (float)z < height; z++) {
            Vector3 position = { (float)x, -0.5f, (float)z };
            DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});
            DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
        }
    }
}

void displayEntity(std::vector<gui::AEntity*> list)
{
    for (auto & i : list) {
        if (dynamic_cast<gui::Player*>(i)) {
            static_cast<gui::Player*>(i)->draw();
        } else {
            DrawModel(i->getModel(), i->getPosition(), i->getScale(), i->getColor());
        }
    }
}

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
    std::vector<gui::AEntity*> list;

    for (int x = 0; (float)x < (width * height) / 2; ++x) {
        int value1 = GetRandomValue(0, (int)width - 1);
        int value2 = GetRandomValue(0, (int)height - 1);

        int isKayu = GetRandomValue(0, 7);

        if (isKayu == 0)
            list.push_back(new gui::Food({(float)value1, 0.05, (float)value2}, 0.7f, BROWN));
        else if (isKayu == 1)
            list.push_back(new gui::Player({(float)value1, 0, (float)value2}, 1.0f, RED, screenWidth, screenHeight));
        else if (isKayu == 2)
            list.push_back(new gui::Linemate({(float)value1, 0.05, (float)value2}, 0.27f, BROWN));
        else if (isKayu == 3)
            list.push_back(new gui::Deraumere({(float)value1, 0.05, (float)value2}, 0.3f, BROWN));
        else if (isKayu == 4)
            list.push_back(new gui::Sibur({(float)value1, 0.05, (float)value2}, 0.07f, BROWN));
        else if (isKayu == 5)
            list.push_back(new gui::Mendiane({(float)value1, 0.05, (float)value2}, 0.025f, WHITE));
        else if (isKayu == 6)
            list.push_back(new gui::Phiras({(float)value1, 0.05, (float)value2}, 0.04f, BLUE));
        else if (isKayu == 7)
            list.push_back(new gui::Thystame({(float)value1, 0.05, (float)value2}, 0.4f, PURPLE));
    }

    // ------ Camera ------
    Camera camera = { { -width, 10.0f, -height}, { width / 2, 0.0f, height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    //--------------------------------------------------------- Display ----------------------------------------------------------------

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            UpdateCamera(&camera, CAMERA_THIRD_PERSON);
            DisableCursor();
        }
        else
            EnableCursor();
        for (auto & i : list)
            if (dynamic_cast<gui::Player*>(i))
                static_cast<gui::Player*>(i)->update(camera);
        BeginDrawing();
        if (camera.position.y < 0.1)
            camera.position.y = 0.1;
        ClearBackground(BLACK);
        BeginMode3D(camera);
        displayMap(width, height);
        displayEntity(list);
        EndMode3D();
        for (auto & i : list)
            if (dynamic_cast<gui::Player*>(i))
                static_cast<gui::Player*>(i)->drawInventory();
        EndDrawing();
    }
    list.clear();
    CloseWindow();

    return 0;
}
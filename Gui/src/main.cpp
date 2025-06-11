/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include "Kayu.hpp"
#include "Button.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Inventory.hpp"

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
        } else if (dynamic_cast<gui::Kayu*>(i)) {
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

        int isKayu = GetRandomValue(0, 1);

        if (isKayu)
            list.push_back(new gui::Kayu({(float)value1, 0.05, (float)value2}, 1.0f, RED));
        else
            list.push_back(new gui::Player({(float)value1, 0, (float)value2}, 1.0f, RED, screenWidth, screenHeight));
    }

    // ------ Camera ------
    Camera camera = { { -width, 10.0f, -height}, { width / 2, 0.0f, height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    //--------------------------------------------------------- Display ----------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // ------ Update ------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        for (auto & i : list) {
            if (dynamic_cast<gui::Player*>(i)) {
                static_cast<gui::Player*>(i)->update(camera);
            }
        }
        BeginDrawing();

        if (camera.position.y < 0.1)
            camera.position.y = 0.1;

        ClearBackground(BLACK);

        BeginMode3D(camera);
        
        displayMap(width, height);
        displayEntity(list);
        
        EndMode3D();

        for (auto & i : list) {
            if (dynamic_cast<gui::Player*>(i)) {
                static_cast<gui::Player*>(i)->drawInventory();
            }
        }

        EndDrawing();
    }
    list.clear();
    CloseWindow();

    return 0;
}
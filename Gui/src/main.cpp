/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include <cstdlib>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/Kayu.hpp"

void displayMap(float width, float height)
{
    for (int x = 0; x < width; x++) {
        for (int z = 0; z < height; z++) {
            Vector3 position = { (float)x, -0.5f, (float)z };
            DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});
            DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
        }
    }
}

void displayEntity(std::vector<Gui::AEntity*> list)
{
    for (int i = 0; i < list.size(); ++i) {
        DrawModel(list[i]->getModel(), list[i]->getPosition(), list[i]->getScale(), list[i]->getColor());
    }
}

#define WIDTH 10
#define HEIGHT 10

int main(void)
{

    //--------------------------------------------------------- Temp brut code ----------------------------------------------------------------
    float width = WIDTH;
    float height = HEIGHT;

    //--------------------------------------------------------- Init ----------------------------------------------------------------

    // ------ Window ------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Zappy");

    SetTargetFPS(60);

    // ------ Brut code for Entity on Map ------

    std::vector<Gui::AEntity*> list;

    for (int x = 0; x < (width * height) / 2; ++x) {
        int value1 = GetRandomValue(0, width - 1);
        int value2 = GetRandomValue(0, height - 1);

        int isKayu = GetRandomValue(0, 1);

        if (isKayu)
            list.push_back(new Gui::Kayu({(float)value1, 0.05, (float)value2}, 1.0f, RED));
        else
            list.push_back(new Gui::Player({(float)value1, 0, (float)value2}, 1.0f, RED));
    }

    // ------ Camera ------

    Camera camera = { { -width, 10.0f, -height}, { width / 2, 0.0f, height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    //--------------------------------------------------------- Display ----------------------------------------------------------------

    DisableCursor();

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        if (camera.position.y < 0.1)
            camera.position.y = 0.1;

        ClearBackground(BLACK);

        BeginMode3D(camera);

        displayEntity(list);

        displayMap(width, height);

        EndMode3D();

        EndDrawing();
    }


    EnableCursor();
    CloseWindow();

    return 0;
}

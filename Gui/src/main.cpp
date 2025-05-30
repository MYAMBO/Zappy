/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main.cpp
*/

#include <cstdlib>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/Kayu.hpp"

/*******************************************************************************************
*
*   raylib [core] example - World to screen
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#define WIDTH 10
#define HEIGHT 10

void displayMap(float width, float height)
{
    for (int x = 0; x < width; x++) {
        for (int z = 0; z < height; z++) {
            Vector3 position = { (float)x, 0.0f, (float)z };
            DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});
            DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
        }
    }
}

void displayEntity(std::vector<Gui::AEntity*> list)
{
    // get list(list(int))

    int id = 0;

        for (int x = 0; x < list.size(); ++x) {
            DrawModel(list[x]->getModel(), list[x]->getPosition(), list[x]->getScale(), list[x]->getColor());
        }
}

int main(void)
{

    //--------------------------------------------------------- Temp brut code ----------------------------------------------------------------
    float width = WIDTH;
    float height = HEIGHT;

    std::vector<std::vector<int>> map((int)height);

    //--------------------------------------------------------- Init ----------------------------------------------------------------

    // ------ For Window ------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "EpiMorse");

    SetTargetFPS(60);


    std::vector<Gui::AEntity*> list;

    for (int x = 0; x < 50; ++x) {
        int value1 = GetRandomValue(0, width - 1);
        int value2 = GetRandomValue(0, height - 1);
        int value3 = GetRandomValue(0, 1);
        if (value3)
            list.push_back(new Gui::Kayu({(float)value1, 0.55, (float)value2}, 1.0f, RED));
        else
            list.push_back(new Gui::Player({(float)value1, 0.5, (float)value2}, 1.0f, RED));
    }

    // ------ For Camera ------
    Camera camera = { { -width, 10.0f, -height}, { width / 2, 0.0f, height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    //--------------------------------------------------------- Display ----------------------------------------------------------------

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        displayEntity(list);

        displayMap(width, height);

        EndMode3D();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}

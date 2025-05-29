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

void displayEntity(std::vector<std::vector<Gui::AEntity *>> list, float  width, float height)
{
    // get list(list(int))

    int id = 0;

    for (int y = 0; y < (int)height; ++y) {
        for (int x = 0; x < (int)width; ++x) {
            DrawModel(*list[y][x]->getModel(), list[y][x]->getPosition(), list[y][x]->getScale(), list[y][x]->getColor());
        }
    }
}

int main(void)
{

    //--------------------------------------------------------- Temp brut code ----------------------------------------------------------------
    float width = WIDTH;
    float height = HEIGHT;

    std::vector<std::vector<int>> map((int)height);

    std::vector<std::vector<Gui::AEntity*>> grid;

    //--------------------------------------------------------- Init ----------------------------------------------------------------

    // ------ For Window ------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "EpiMorse");

    SetTargetFPS(60);

    std::cout << "toto" << std::endl;

    for (int y = 0; y < (int)height; ++y) {
        std::vector<Gui::AEntity*> row;
        for (int x = 0; x < (int)width; ++x) {
            row.push_back(new Gui::Kayu({(float)x, 0.55,(float)y}, 1.0f, RED));
        }
        grid.push_back(row);
    }
    std::cout << "tourte" << std::endl;

    // ------ For Camera ------
    Camera camera = { { -width, 10.0f, -height}, { width / 2, 0.0f, height / 2 }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    //--------------------------------------------------------- Display ----------------------------------------------------------------

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        displayEntity(grid ,width, height);

        displayMap(width, height);

        EndMode3D();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}

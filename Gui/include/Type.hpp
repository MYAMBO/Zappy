/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Type
*/

#ifndef ZAPPY_TYPE_HPP
    #define ZAPPY_TYPE_HPP

    #include <string>
    #include <vector>
    #include <memory>
    #include <raylib.h>

    #define WIDTH 10
    #define HEIGHT 10

    #define TARGET_FPS 60
    #define SCREEN_WIDTH GetScreenWidth()
    #define SCREEN_HEIGHT GetScreenHeight()

namespace gui {
    enum Orientation {
        North = 1,
        Est = 2,
        South = 3,
        West = 4
    };

    enum CamState {
        EXIT = 0,
        WORLD = 1,
        PLAYER = 2
    };

    enum class SceneState {
        MENU = 0,
        GAME = 1,
        SETTINGS = 2,
        EXIT = 3
    };
};



#endif // ZAPPY_TYPE_HPP
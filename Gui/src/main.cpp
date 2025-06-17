/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include "Scene.hpp"

int main()
{
    gui::Scene scene;
    
    while (scene.isOpen()) {
        scene.update();
    }
    
    return 0;
}
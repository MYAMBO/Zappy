/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Display
*/

#ifndef ZAPPY_DISPLAY_HPP
#define ZAPPY_DISPLAY_HPP

    #include "Egg.hpp"
    #include "Tile.hpp"
    #include "Food.hpp"
    #include "Type.hpp"
    #include "Sibur.hpp"
    #include "AItem.hpp"
    #include "Button.hpp"
    #include "Logger.hpp"
    #include "Phiras.hpp"
    #include "Linemate.hpp"
    #include "Mendiane.hpp"
    #include "Thystame.hpp"
    #include "Inventory.hpp"
    #include "Deraumere.hpp"

    #include <vector>
    #include <memory>
    #include <math.h>
    #include <raylib.h>
    #include <iostream>

namespace gui {
    namespace ui {
        class Menu;
        class Settings;
    }
    class Player;
    class Client;
    class Display {
        public:
            Display(std::shared_ptr<Camera> camera, std::shared_ptr<CamState> camState, std::shared_ptr<SceneState> sceneState, std::shared_ptr<int> timeUnit);
            
            ~Display();

            /**
             * @brief Render the 3D scene and UI elements.
             */
            void render();

            /**
             * @brief Handle user input for camera and entity control.
             */
            void handleInput();

            void addPlayer(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team);

            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> getMap();
            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> getEggs();
            std::shared_ptr<std::vector<std::shared_ptr<Model>>> getModels();
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> getPlayers();

            std::unique_ptr<ui::Menu> _menu;
            std::unique_ptr<ui::Settings> _settings;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> _players;

            std::shared_ptr<Model> _model;
            std::shared_ptr<Model> _eggModel;
            Model _deadModel;
            ModelAnimation *_animations;
            int _animCount;
        private:
            /**
             * @brief Display all entities in the 3D scene.
             */
            void displayEntity();

            /**
             * @brief Handle input for toggling item display visibility.
             */
            void eventToggleDisplay();

            /**
             * @brief Initialize orbital camera around a target.
             */
            void initOrbitalCamera(const Vector3& target, float distance);

            /**
             * @brief Update camera based on current state and player selection.
             */
            void updateCamera();

            std::shared_ptr<int> _timeUnit;
            std::shared_ptr<Camera> _camera;
            std::shared_ptr<Client> _client;
            std::shared_ptr<CamState> _camState;
            std::shared_ptr<SceneState> _sceneState;
            std::shared_ptr<std::vector<std::shared_ptr<Model>>> _models;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> _eggs;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> _map;

            std::vector<int> _itemDisplay;
            float _width;
            float _height;
    };
};

#endif // ZAPPY_DISPLAY_HPP
/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/

#ifndef ZAPPY_SCENE_HPP
    #define ZAPPY_SCENE_HPP

    #include "Egg.hpp"
    #include "Tile.hpp"
    #include "Food.hpp"
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
    #include <raylib.h>
    #include <iostream>

    #define WIDTH 10
    #define HEIGHT 10

    #define SCREEN_WIDTH 1920
    #define SCREEN_HEIGHT 1080
    #define TIME_UNIT 1
    #define TARGET_FPS 60

    
namespace gui {
    namespace ui {
        class Menu;
        class Settings;
    };
    class Client;
    class Player;

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

    class Scene {
        public:
            Scene();
            ~Scene();
            
            /**
             * @brief Check if the scene is open and not closed by the user.
             * @return true if the scene is open, false otherwise.
             */
            bool isOpen() const;
            
            /**
             * @brief Update the scene based on the current state.
             * This function handles input, updates entities, and renders the scene.
             */
            void update();
            
            /**
             * @brief Render the scene.
             * This function draws the 3D scene and the UI elements.
             */
            void render();
            
            /**
             * @brief Handle input from the user.
             * This function processes user input to control the camera and entities.
             */
            void initWindow();
            
            /**
             * @brief Handle user input for controlling the camera and entities.
             * This function processes keyboard and mouse input to change the camera state and control player actions.
             */
            void handleInput();
            
            /**
             * @brief Display entities in the scene.
             * This function draws all entities (items and players) in the 3D scene.
             */
            void displayEntity();
            
            /**
             * @brief Event handler for toggling item display.
             * This function handles the events for toggling the display of items based on user input.
             */
            void eventToggleDisplay();
            
            void initOrbitalCamera(const Vector3& target, float distance);

        private:
            std::shared_ptr<Camera> _camera;
            std::shared_ptr<CamState> _camState;
            
            bool _isOpen;
            float _width;
            float _height;
            
            SceneState _currentState;
            std::shared_ptr<Client> _client;
            
            std::unique_ptr<ui::Menu> _menu;
            std::unique_ptr<ui::Settings> _settings;
            
            std::shared_ptr<Model> _playerModel;
            
            std::vector<int> _itemDisplay;
            std::shared_ptr<std::vector<std::shared_ptr<Model>>> _models;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> _eggs;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> _map;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> _players;

            static std::shared_ptr<Model> safeModelLoader(const std::string& string);
        };

    class FailedLoadModel : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Failed to load a model, make sure there is no error.";
        };
    };
};

#endif // ZAPPY_SCENE_HPP
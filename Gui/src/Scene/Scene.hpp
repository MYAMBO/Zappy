/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scene
*/

#ifndef ZAPPY_SCENE_HPP
#define ZAPPY_SCENE_HPP

#include "Type.hpp"
#include "Display.hpp"

#include <vector>
#include <memory>
#include <raylib.h>
#include <iostream>

namespace gui {
    class Client;
    class Player;

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

        private:
            /**
             * @brief Initialize the window and basic settings.
             */
            void initWindow();

            /**
             * @brief Handle state-specific input and logic.
             */
            void handleStateLogic();

            bool _isOpen;
            
            std::shared_ptr<int> _timeUnit;
            std::shared_ptr<Client> _client;
            std::shared_ptr<Display> _display;

            std::shared_ptr<Camera> _camera;
            std::shared_ptr<CamState> _camState;
            std::shared_ptr<SceneState> _currentState;

            /**
             * @brief Safe model loader with error handling.
             */
            static std::shared_ptr<Model> safeModelLoader(const std::string& path);
    };

    class FailedLoadModel : public std::exception {
        public:
            [[nodiscard]] const char *what() const noexcept override {
                return "Failed to load a model, make sure there is no error.";
            };
    };
};

#endif // ZAPPY_SCENE_HPP
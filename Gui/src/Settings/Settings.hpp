/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Settings
*/

#ifndef ZAPPY_SETTINGS_HPP
    #define ZAPPY_SETTINGS_HPP

    #include <vector>
    #include <string>

    #include "Scene.hpp"
    #include "Button.hpp"

namespace gui {
    namespace ui {
        class Settings {
            public:
                Settings(SceneState &sceneSate, int screenWidth, int screenHeight);
                ~Settings();

                /**
                 * @brief Initialize settings UI elements.
                 * This function initializes the UI elements for the settings menu.
                 */
                void initSettingsUI();

                /**
                 * @brief Handle inputs for the settings menu.
                 * This function processes user inputs in the settings menu, such as button clicks.
                 */
                void handleSettingsInputs();

                /**
                 * @brief Draw the settings menu.
                 * This function renders the settings menu on the screen.
                 */
                void drawSettings();

            private:
                /**
                 * @brief Handle the action when the back button is clicked.
                 * This function sets the scene state to MENU when the back button is clicked.
                 */
                void backButtonClicked();

                /**
                 * @brief Initialize the resource items
                 */
                void initResourceItems();

                /**
                 * @brief Initialize camera control information
                 */
                void initCameraControls();

                SceneState &_sceneState;
                Button _backButton;
                
                int _screenWidth;
                int _screenHeight;

                Camera3D _camera;
                Rectangle _legendBox;
                Rectangle _commandBox;
                Rectangle _cameraBox;

                // Resource controls
                std::vector<Color> _color;
                std::vector<Rectangle> _box;
                std::vector<std::string> _key;
                std::vector<std::string> _name;
                
                // Camera controls
                std::vector<std::string> _cameraKeys;
                std::vector<std::string> _cameraActions;
        };
    }
}

#endif
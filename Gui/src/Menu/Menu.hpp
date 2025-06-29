/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Menu
*/

#ifndef ZAPPY_MENU_HPP
    #define ZAPPY_MENU_HPP

    #include <string>
    #include <raylib.h>

    #include "Scene.hpp"

namespace gui {
    namespace ui {
        class Menu {
            public:
                Menu(std::shared_ptr<SceneState> sceneState);
                ~Menu();

                /**
                 * @brief Handle input for menu state.
                 */
                void handleMenuInput();

                /**
                 * @brief Handle text input for server ID.
                 */
                void handleTextInput();

                /**
                 * @brief Draw the main menu screen.
                 */
                void drawMainMenu();

                /**
                 * @brief Initialize menu UI elements.
                 */
                void initMenuUI();

            private:
                /**
                 * @brief Handle the action when the play button is clicked.
                 */
                void playClicked();

                /**
                 * @brief Close the window and exit the application.
                 */
                void closeWindow();

                /**
                 * @brief Handle the action when the settings button is clicked.
                 */
                void settingClicked();

                std::shared_ptr<SceneState> _sceneState;
                int _frameCounter;
                bool _serverIdActive;
                std::string _serverId;

                Button _playButton;
                Button _exitButton;
                Button _settingButton;

                Rectangle _serverIdBox;

                Color _inputBoxColor;
                Color _backgroundColor;
                Color _inputBoxActiveColor;

                int _errorInput;
                int _screenWidth;
                int _screenHeight;
                int _titleFontSize;
                int _inputFontSize;
                int _buttonFontSize;
                
                static const int MAX_SERVER_ID_LENGTH = 50;
        };
    };
};

#endif // ZAPPY_MENU_HPP
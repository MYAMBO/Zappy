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
    #include "Button.hpp"

namespace gui {
    namespace ui {
        class Menu {
            public:
                Menu(SceneState &sceneState, int screenWidth, int screenHeight);
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
                 * @brief Draw the connecting screen.
                 */
                void drawConnectingScreen();

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

                SceneState &_sceneState;
                int _frameCounter;
                bool _serverIdActive;
                std::string _serverId;

                Button _playButton;
                Button _exitButton;

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
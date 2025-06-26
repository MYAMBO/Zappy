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

    #include "Type.hpp"
    #include "Scene.hpp"
    #include "Button.hpp"

namespace gui {
    namespace ui {
        class Menu {
            public:
                Menu(std::shared_ptr<SceneState> sceneState, std::function<void()> function);
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
                * @brief Draw the text area.
                */
                void drawTextBox(int errorNb, bool active, Rectangle box, int height, const std::string& name, const std::string& errorStr);

                /**
                 * @brief Draw the connecting screen.
                 */
                void drawConnectingScreen();

                /**
                 * @brief Initialize menu UI elements.
                 */
                void initMenuUI();

                /**
                 *
                 * @brief Setter for Hostname
                 */
                void setHostname(std::shared_ptr<std::string> name);

                /**
                 *
                 * @brief Setter for Port
                 */
                void setPort(std::shared_ptr<std::string> name);

                /**
                 *
                 * @brief Getter for Hostname
                 */
                std::shared_ptr<std::string> getHostname();

                /**
                 *
                 * @brief Getter for Port
                 */
                std::shared_ptr<std::string> getPort();

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

                std::function<void()> _connectionFunction;
                std::shared_ptr<SceneState> _sceneState;
                int _frameCounter;
                bool _hostnameActive;
                bool _portActive;
                std::shared_ptr<std::string> _hostname;
                std::shared_ptr<std::string> _port;

                Button _playButton;
                Button _exitButton;
                Button _settingButton;

                Rectangle _hostnameBox;
                Rectangle _portBox;

                Color _inputBoxColor;
                Color _backgroundColor;
                Color _inputBoxActiveColor;

                int _hostnameError;
                int _portError;
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
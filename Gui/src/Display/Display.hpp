/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Display
*/

#ifndef ZAPPY_DISPLAY_HPP
#define ZAPPY_DISPLAY_HPP

    #include "Tile.hpp"
    #include "TeamsDisplay.hpp"

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

            /**
             * @brief Set the end game UI and display the winner.
             * @param team The name of the winning team.
             * This function sets the end game UI and displays the winning team.
             */
            void setWinner(const std::string& team);

            void addPlayer(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team);

            std::shared_ptr<std::vector<std::shared_ptr<Tile>>> getMap();
            std::shared_ptr<std::vector<std::shared_ptr<Egg>>> getEggs();
            std::shared_ptr<std::vector<std::shared_ptr<Model>>> getModels();
            std::shared_ptr<std::vector<std::shared_ptr<Player>>> getPlayers();

            void setTeams(std::shared_ptr<std::vector<std::string>> teams);
            void setTeamsColors(std::shared_ptr<std::map<std::string, Color>> teamColors);
            void setDisplayTeams(std::shared_ptr<TeamsDisplay> displayTeams);

            std::unique_ptr<ui::Menu> _menu;
            std::unique_ptr<ui::Settings> _settings;
            std::shared_ptr<std::vector<std::shared_ptr<Player>>> _players;

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

            /**
             * @brief Display the teams in the UI.
             */
            void teamsDisplay();

            /**
             * @brief Display the end game UI.
             */
            void endGameUI();

            /**
             * @brief End the game and display.
             */
            void endGame();


            void drawOverlay(Color color = Fade(BLACK, 0.8f));

            float fadeInAnimation(float duration, bool reset);
            Color glowEffect(Color baseColor, float speed, float intensity);
            Rectangle drawCenteredPanel(int width, int height, Color bgColor);
            std::string typingEffect(std::string fullText, float speed, bool reset);
            void drawNotification(std::string message, float duration, Color bgColor, bool reset);
            void drawSeparatorLine(Rectangle container, float yOffset, Color color, float thickness);
            Vector2 drawCenteredText(std::string text, float y, float fontSize, Color color, Rectangle container);
            bool drawButton(Rectangle bounds, std::string text, Color normalColor, Color hoverColor, Color textColor);
            void drawPulsingText(std::string text, Rectangle container, float fontSize, Color color, float pulseSpeed, float pulseAmount);
            void drawTextWithShadow(std::string text, Vector2 position, float fontSize, Color textColor, Color shadowColor,  Vector2 shadowOffset);


            bool _winner = false;
            std::string _winnerTeam;
            std::shared_ptr<int> _timeUnit;
            std::shared_ptr<Camera> _camera;
            std::shared_ptr<CamState> _camState;
            std::shared_ptr<SceneState> _sceneState;
            std::shared_ptr<TeamsDisplay> _displayTeams;
            std::shared_ptr<std::vector<std::string>> _teams;
            std::shared_ptr<std::map<std::string, Color>> _teamColors;
            std::shared_ptr<std::vector<std::shared_ptr<Model>>> _models;
            std::shared_ptr<std::vector<std::shared_ptr<Egg>>> _eggs;
            std::shared_ptr<std::vector<std::shared_ptr<Tile>>> _map;

            std::vector<int> _itemDisplay;
            float _width;
            float _height;
    };
};

#endif // ZAPPY_DISPLAY_HPP
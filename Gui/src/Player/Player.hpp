/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.hpp
*/

#ifndef ZAPPY_PLAYER_HPP
    #define ZAPPY_PLAYER_HPP

    #include <tuple>

    #include "Scene.hpp"
    #include "Button.hpp"
    #include "AEntity.hpp"
    #include "Inventory.hpp"

enum Orientation {
    North,
    Est,
    South,
    West
};

namespace gui {
    class Player : public AEntity {
        public:
            Player(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team, float scale, int screenWidth, int screenHeight, Camera3D &camera, int &sceneState);
            ~Player();

            int getId() const;
            int getLevel() const;
            Orientation getOrientation() const;
            std::string getTeam() const;

            void setLevel(int level);
            void setOrientation(Orientation orientation);

            /**
             * @brief Draw the Player on the screen.
             * This function draws the Player.
             */
            void draw();

            /**
             * @brief Draw the UI of the Player.
             * This function draws the UI of the Player.
             */
            void drawUI();

            /**
             * @brief Handle the camera button action.
             * This function handles the action when the camera button is clicked.
             */
            void HandleCamButton(Camera3D &camera, CamState &sceneState);

            /**
             * @brief Update the Player.
             * This function updates the Player's state based on user input.
             * @param camera The Camera3D used for ray picking.
             * @return An integer indicating the result of the update (e.g., success or failure).
             */
            int update(Camera3D camera);

            /**
             * @brief Update the UI of the Player.
             * This function updates the UI of the Player.
             */
            void updateUI();
        private:
            int _id;
            int _level;
            std::string _team;
            bool _isSelected = false;

            ui::Button _camButton;
            Orientation _direction;
            ui::Inventory _inventory;
    };
}

#endif //ZAPPY_PLAYER_HPP

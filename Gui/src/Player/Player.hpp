/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.hpp
*/

#ifndef ZAPPY_PLAYER_HPP
    #define ZAPPY_PLAYER_HPP

    #include <tuple>
    #include "AEntity.hpp"
    #include "Inventory.hpp"

enum orientation {
    North,
    Est,
    South,
    West
};

namespace gui {
    class Player : public AEntity {
        public:
            Player(Vector3 position, float scale, Color color, int screenWidth, int screenHeight);
            ~Player();

            /**
             * @brief Move the model to the left.
             * This function changes the direction of the model to the left.
             */
            void Left();

            /**
             * @brief Draw the Player on the screen.
             * This function draws the Player.
             */
            void draw();

            /**
             * @brief Move the model to the right.
             * This function changes the direction of the model to the right.
             */
            void Right();

            /**
             * @brief Move the model forward.
             * This function moves the model in the current direction.
             */
            void forward();

            /**
             * @brief Draw the UI of the Player.
             * This function draws the UI of the Player.
             */
            void drawUI();

            /**
             * @brief Update the Player.
             * This function updates the Player's state based on user input.
             * @param camera The Camera3D used for ray picking.
             * @return An integer indicating the result of the update (e.g., success or failure).
             */
            int update(Camera3D camera);
        private:
            bool _isSelected = false;

            orientation _direction;
            ui::Inventory _inventory;
    };
};

#endif

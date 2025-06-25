/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Egg
*/

#ifndef ZAPPY_EGG_HPP
    #define ZAPPY_EGG_HPP

    #include "AEntity.hpp"

namespace gui {
    class Egg : public AEntity {
        public:
            Egg(int id, std::pair<int, int> position, std::shared_ptr<Model> model);
            ~Egg();

            /**
             * @brief Draw the Egg in the scene.
             * This function draws the Egg model at its current position with its scale and color.
             */
            void draw();

            /**
             * @brief Check if the Egg is cracked at a specific position.
             * This function checks if the Egg's position matches the given position.
             * @param position The position to check against the Egg's position.
             * @return true if the Egg is cracked at the given position, false otherwise.
             */
            bool crackEgg(std::pair<int, int> position);
        private:
            int _id;
    };
};

#endif
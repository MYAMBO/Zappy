/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Inventory
*/

#ifndef INVENTORY_HPP_
    #define INVENTORY_HPP_

    #include <string>
    #include <raylib.h>

namespace gui {
    namespace ui {
        class Inventory {
            public:
                Inventory(int screenWidth, int screenHeight);
                ~Inventory();
        
                /**
                 * @brief Draw the Inventory on the screen.
                 * This function draws the Inventory.
                 */
                void draw();

                /**
                 * @brief Setter for the bounds.
                 * This functions allow you to set the bounds.
                 * @param bounds The rectangle defining the Inventory's position and size.
                 */
                void setBounds(Rectangle bounds);

                /**
                 * @brief Getter for the bounds.
                 * This function returns the rectangle defining the Inventory's position and size.
                 * @return The bounds of the Inventory.
                 */
                Rectangle getBounds() const;
        
            private:
                int _fontSize;

                Rectangle _bounds;
        };
    }
}

#endif
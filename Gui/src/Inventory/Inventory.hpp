/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Inventory
*/

#ifndef INVENTORY_HPP_
    #define INVENTORY_HPP_

    #include <map>
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
        
                /**
                 * @brief Set the quantity of an item in the inventory.
                 * This function allows you to set the quantity of a specific item in the inventory.
                 * @param item The name of the item.
                 * @param quantity The quantity of the item to set.
                 */
                void setInventoryItem(const std::string& item, int quantity);

                /**
                 * @brief Get the quantity of an item in the inventory.
                 * This function returns the quantity of a specific item in the inventory.
                 * @param item The name of the item.
                 * @return The quantity of the item, or 0 if the item does not exist.
                 */
                int getInventoryItem(const std::string& item) const;

            private:
                int _fontSize;
                std::map<std::string, std::pair<int, Color>> _items;

                Rectangle _bounds;
        };
    }
}

#endif
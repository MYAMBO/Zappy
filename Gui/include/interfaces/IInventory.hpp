/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IInventory.hpp
*/

#ifndef ZAPPY_IINVENTORY_HPP
    #define ZAPPY_IINVENTORY_HPP

    #include <map>
    #include <string>
    #include <raylib.h>

namespace gui {
    namespace ui {
        class IInventory {
        public:
            /**
             *@brief Function to draw everything
             */
            virtual void draw() = 0;

            /**
             * @brief Setter for the bounds.
             * This functions allow you to set the bounds.
             * @param bounds The rectangle defining the Inventory's position and size.
             */
            virtual void setBounds(Rectangle bounds) = 0;

            /**
             * @brief Getter for the bounds.
             * This function returns the rectangle defining the Inventory's position and size.
             * @return The bounds of the Inventory.
             */
            virtual Rectangle getBounds() const = 0;

            /**
             * @brief Set the quantity of an item in the inventory.
             * This function allows you to set the quantity of a specific item in the inventory.
             * @param item The name of the item.
             * @param quantity The quantity of the item to set.
             */
            virtual void setInventoryItem(const std::string &item, int quantity) = 0;

            /**
             * @brief Get the quantity of an item in the inventory.
             * This function returns the quantity of a specific item in the inventory.
             * @param item The name of the item.
             * @return The quantity of the item, or 0 if the item does not exist.
             */
            virtual int getInventoryItem(const std::string &item) const = 0;
        protected:
            /**
             * @brief Draw the background of the inventory.
             */
            virtual void drawBackground() = 0;

            /**
             * @brief Draw the items and qty for inventory.
             */
            virtual void drawItems() = 0;
        };
    }
}

#endif //ZAPPY_IINVENTORY_HPP

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AInventory.hpp
*/

#ifndef ZAPPY_AINVENTORY_HPP
    #define ZAPPY_AINVENTORY_HPP

    #include "IInventory.hpp"

namespace gui {
    namespace ui {
        class AInventory : public IInventory{
        public:
            AInventory(int screenWidth, int screenHeight);
            ~AInventory();

            /**
             * @brief Draw the Inventory on the screen.
             * This function draws the Inventory.
             */
            void draw() override;

            /**
             * @brief Setter for the bounds.
             * This functions allow you to set the bounds.
             * @param bounds The rectangle defining the Inventory's position and size.
             */
            void setBounds(Rectangle bounds) override;

            /**
             * @brief Getter for the bounds.
             * This function returns the rectangle defining the Inventory's position and size.
             * @return The bounds of the Inventory.
             */
            Rectangle getBounds() const override;

            /**
             * @brief Set the quantity of an item in the inventory.
             * This function allows you to set the quantity of a specific item in the inventory.
             * @param item The name of the item.
             * @param quantity The quantity of the item to set.
             */
            void setInventoryItem(const std::string &item, int quantity) override;

            /**
             * @brief Get the quantity of an item in the inventory.
             * This function returns the quantity of a specific item in the inventory.
             * @param item The name of the item.
             * @return The quantity of the item, or 0 if the item does not exist.
             */
            int getInventoryItem(const std::string &item) const override;

        private:
            int _fontSize;
            std::map<std::string, std::pair<int, Color>> _items;

            Rectangle _bounds;
        };
    }
}

#endif //ZAPPY_AINVENTORY_HPP

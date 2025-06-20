/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile.hpp
*/

#ifndef ZAPPY_TILE_HPP
    #define ZAPPY_TILE_HPP

    #include <map>
    #include <memory>
    #include <utility>
    #include <raylib.h>

    #include "Food.hpp"
    #include "Sibur.hpp"
    #include "Phiras.hpp"
    #include "Linemate.hpp"
    #include "Mendiane.hpp"
    #include "Thystame.hpp"
    #include "Deraumere.hpp"

namespace gui {
    class Tile {
        public:
            Tile(std::pair<int, int> coord, std::vector<int> qty, std::vector<std::shared_ptr<Model>> model);
            ~Tile();

            /**
             * @brief Display the tile with its items.
             * This function draws the tile and its items on the screen.
             * @param displayItem A vector containing the IDs of items to be displayed.
             */
            void displayTile(std::vector<int> displayItem);

            enum Type {
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME
            };
            /**
             * @brief Add an item to the tile.
             * This function adds a specified quantity of an item to the tile.
             * @param qty The quantity of the item to add.
             * @param itemId The ID of the item type to add.
             */
            void addItem(int qty, int itemId);

            /**
             * @brief Delete an item from the tile.
             * This function removes a specified quantity of an item from the tile.
             * @param qty The quantity of the item to remove.
             * @param type The ID of the item type to remove.
             */
            void delItem(int qty, int type);

        private:
            std::vector<int> _qty;
            std::pair<int, int> _coord;
            std::vector<std::shared_ptr<Model>> _models;
            std::vector<std::vector<std::shared_ptr<gui::AItem>>> _items;
    };
};

#endif //ZAPPY_TILE_HPP

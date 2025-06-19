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
    #include <raylib.h>
    #include <utility>

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

            void displayTile();

            enum Type {
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME
            };

            void addItem(int qty, int itemId);
            void delItem(int qty, int type);

    private:

            std::vector<std::vector<std::shared_ptr<gui::AItem>>> _items;

            std::vector<int> _qty;

            std::vector<std::shared_ptr<Model>> _models;

            std::pair<int, int> _coord;
    };
};

#endif //ZAPPY_TILE_HPP

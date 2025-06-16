/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile.hpp
*/

#ifndef ZAPPY_TILE_HPP
    #define ZAPPY_TILE_HPP

    #include <utility>
    #include <memory>
    #include "Food.hpp"
    #include "Linemate.hpp"
    #include "Deraumere.hpp"
    #include "Sibur.hpp"
    #include "Mendiane.hpp"
    #include "Phiras.hpp"
    #include "Thystame.hpp"

namespace gui {
    class Tile {
        public:
            Tile(std::pair<int, int> coord, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
            ~Tile();
        private:
            void addFood(int qty);
            void addLinemate(int qty);
            void addDeraumere(int qty);
            void addSibur(int qty);
            void addMendiane(int qty);
            void addPhiras(int qty);
            void addThystame(int qty);

            void delFood(int qty);
            void delLinemate(int qty);
            void delDeraumere(int qty);
            void delSibur(int qty);
            void delMendiane(int qty);
            void delPhiras(int qty);
            void delThystame(int qty);

            std::vector<gui::Food> _food;
            std::vector<gui::Linemate> _linemate;
            std::vector<gui::Deraumere> _deraumere;
            std::vector<gui::Sibur> _sibur;
            std::vector<gui::Mendiane> _mendiane;
            std::vector<gui::Phiras> _phiras;
            std::vector<gui::Thystame> _thystame;

            int _foodQty;
            int _linemateQty;
            int _deraumereQty;
            int _siburQty;
            int _mendianeQty;
            int _phirasQty;
            int _thystameQty;

            std::pair<int, int> _coord;
    };
};

#endif //ZAPPY_TILE_HPP

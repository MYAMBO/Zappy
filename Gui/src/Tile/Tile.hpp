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
            Tile(std::pair<int, int> coord, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
            ~Tile();

            /**
             * @brief displayTile
             * This function displays the items on the tile based on the provided item display map.
             * @param itemDisplay A map containing the display status of each item type.
             * The keys are item names (e.g., "Food", "Linemate")
             * and the values are integers indicating whether to display (1) or not (0).
             */
            void displayTile(std::map<std::string, int> itemDisplay) const;

        private:
            void addFood(int qty);
            void addSibur(int qty);
            void addPhiras(int qty);
            void addLinemate(int qty);
            void addMendiane(int qty);
            void addThystame(int qty);
            void addDeraumere(int qty);

            void delFood(int qty);
            void delSibur(int qty);
            void delPhiras(int qty);
            void delLinemate(int qty);
            void delThystame(int qty);
            void delMendiane(int qty);
            void delDeraumere(int qty);

            std::vector<std::shared_ptr<gui::Food>> _food;
            std::vector<std::shared_ptr<gui::Sibur>> _sibur;
            std::vector<std::shared_ptr<gui::Phiras>> _phiras;
            std::vector<std::shared_ptr<gui::Mendiane>> _mendiane;
            std::vector<std::shared_ptr<gui::Thystame>> _thystame;
            std::vector<std::shared_ptr<gui::Linemate>> _linemate;
            std::vector<std::shared_ptr<gui::Deraumere>> _deraumere;

            int _foodQty;
            int _siburQty;
            int _phirasQty;
            int _linemateQty;
            int _mendianeQty;
            int _thystameQty;
            int _deraumereQty;

            std::pair<int, int> _coord;
    };
};

#endif //ZAPPY_TILE_HPP

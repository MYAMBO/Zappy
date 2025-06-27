/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PlayerInventory.hpp
*/

#ifndef ZAPPY_PLAYERINVENTORY_HPP
    #define ZAPPY_PLAYERINVENTORY_HPP

#include "AInventory.hpp"

namespace gui::ui {
    class PlayerInventory : public AInventory {
    public:
        void draw() override;

        void drawPlayerInformation();

    private:
        int _id;
        int _level;
        Color _color;
        std::string _team;
        std::map<int, std::string> _playersNames;

    };
}

#endif //ZAPPY_PLAYERINVENTORY_HPP

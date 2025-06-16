/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

#include <utility>

gui::Tile::Tile(std::pair<int, int> coord, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame) : _coord(std::move(coord)), _foodQty(food), _linemateQty(linemate), _deraumereQty(deraumere), _siburQty(sibur), _mendianeQty(mendiane), _phirasQty(phiras), _thystameQty(thystame)
{
    this->addFood(food);
    this->addLinemate(linemate);
    this->addDeraumere(deraumere);
    this->addSibur(sibur);
    this->addMendiane(mendiane);
    this->addPhiras(phiras);
    this->addThystame(thystame);
}

gui::Tile::~Tile()
{
}

void gui::Tile::addFood(int qty)
{
    for (int i = 0; i < qty; ++i)
        this->_food.emplace_back(this->_coord, 1);
}

void gui::Tile::addLinemate(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_linemate.emplace_back(this->_coord, 1);
}

void gui::Tile::addDeraumere(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_deraumere.emplace_back(this->_coord, 1);
}

void gui::Tile::addSibur(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_sibur.emplace_back(this->_coord, 1);
}

void gui::Tile::addMendiane(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_mendiane.emplace_back(this->_coord, 1);
}

void gui::Tile::addPhiras(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_phiras.emplace_back(this->_coord, 1);
}

void gui::Tile::addThystame(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_thystame.emplace_back(this->_coord, 1);
}


void gui::Tile::delFood(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_food.pop_back();
}

void gui::Tile::delLinemate(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_linemate.pop_back();
}

void gui::Tile::delDeraumere(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_deraumere.pop_back();
}

void gui::Tile::delSibur(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_sibur.pop_back();
}

void gui::Tile::delMendiane(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_mendiane.pop_back();
}

void gui::Tile::delPhiras(int qty)
{
    for (int i = 0; i < qty; ++i)
        this->_phiras.pop_back();
}

void gui::Tile::delThystame(int qty)
{
    for (int i = 0; i < qty; ++i)
        this->_thystame.pop_back();
}

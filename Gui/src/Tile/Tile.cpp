/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

#include <utility>

gui::Tile::Tile(std::pair<int, int> coord, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame) : _foodQty(food), _linemateQty(linemate), _deraumereQty(deraumere), _siburQty(sibur), _mendianeQty(mendiane), _phirasQty(phiras), _thystameQty(thystame), _coord(std::move(coord))
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
        this->_food.emplace_back(std::make_shared<Food>(this->_coord, 0.7));
}

void gui::Tile::addLinemate(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_linemate.emplace_back(std::make_shared<Linemate>(this->_coord, 0.27));
}

void gui::Tile::addDeraumere(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_deraumere.emplace_back(std::make_shared<Deraumere>(this->_coord, 0.3));
}

void gui::Tile::addSibur(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_sibur.emplace_back(std::make_shared<Sibur>(this->_coord, 0.07));
}

void gui::Tile::addMendiane(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_mendiane.emplace_back(std::make_shared<Mendiane>(this->_coord, 0.025));
}

void gui::Tile::addPhiras(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_phiras.emplace_back(std::make_shared<Phiras>(this->_coord, 0.04));
}

void gui::Tile::addThystame(int qty)
{
    for (int i = 0; i < qty; ++i)
       this->_thystame.emplace_back(std::make_shared<Thystame>(this->_coord, 0.4));
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

void gui::Tile::displayTile()
{
    for (auto food: this->_food)
        DrawModel(food->getModel(), food->getPosition(), food->getScale(), food->getColor());
    for (auto linemate: this->_linemate)
        DrawModel(linemate->getModel(), linemate->getPosition(), linemate->getScale(), linemate->getColor());
    for (auto deraumere: this->_deraumere)
        DrawModel(deraumere->getModel(), deraumere->getPosition(), deraumere->getScale(), deraumere->getColor());
    for (auto sibur: this->_sibur)
        DrawModel(sibur->getModel(), sibur->getPosition(), sibur->getScale(), sibur->getColor());
    for (auto mendiane: this->_mendiane)
        DrawModel(mendiane->getModel(), mendiane->getPosition(), mendiane->getScale(), mendiane->getColor());
    for (auto phiras: this->_phiras)
        DrawModel(phiras->getModel(), phiras->getPosition(), phiras->getScale(), phiras->getColor());
    for (auto thystame: this->_thystame)
        DrawModel(thystame->getModel(), thystame->getPosition(), thystame->getScale(), thystame->getColor());

    Vector3 position = {(float)this->_coord.first, 0, (float)this->_coord.second};
    DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});
    DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
}

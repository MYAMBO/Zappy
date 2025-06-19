/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile.cpp
*/

#include <utility>

#include "Tile.hpp"

#include <utility>
#include <functional>



/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Tile::Tile(std::pair<int, int> coord, std::vector<int> qty, std::vector<std::shared_ptr<Model>> model) : _items(7) ,_qty(qty), _models(std::move(model)), _coord(std::move(coord))
{
    std::vector<std::shared_ptr<gui::AItem>> list;

    this->addItem(qty[FOOD], FOOD);
    this->addItem(qty[LINEMATE], LINEMATE);
    this->addItem(qty[DERAUMERE], DERAUMERE);
    this->addItem(qty[SIBUR], SIBUR);
    this->addItem(qty[MENDIANE], MENDIANE);
    this->addItem(qty[PHIRAS], PHIRAS);
    this->addItem(qty[THYSTAME], THYSTAME);
}

gui::Tile::~Tile()
{
}

/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void gui::Tile::addItem(int qty, int type)
{
    const std::unordered_map<int, std::function<std::shared_ptr<gui::AItem>()>> factoryMap = {
        { FOOD,      [this]() { return std::make_shared<gui::Food>(this->_coord, 0.7, this->_models[FOOD]); } },
        { LINEMATE,  [this]() { return std::make_shared<gui::Linemate>(this->_coord, 0.27, this->_models[LINEMATE]); } },
        { DERAUMERE, [this]() { return std::make_shared<gui::Deraumere>(this->_coord, 0.3, this->_models[DERAUMERE]); } },
        { SIBUR,     [this]() { return std::make_shared<gui::Sibur>(this->_coord, 0.07, this->_models[SIBUR]); } },
        { MENDIANE,  [this]() { return std::make_shared<gui::Mendiane>(this->_coord, 0.025, this->_models[MENDIANE]); } },
        { PHIRAS,    [this]() { return std::make_shared<gui::Phiras>(this->_coord, 0.04, this->_models[PHIRAS]); } },
        { THYSTAME,  [this]() { return std::make_shared<gui::Thystame>(this->_coord, 0.4, this->_models[THYSTAME]); } }
    };

    auto it = factoryMap.find(type);
    if (it == factoryMap.end())
        throw ;

    for (int i = 0; i < qty; ++i)
        this->_items[type].emplace_back(it->second());
    this->_qty[type] += qty;
}


void gui::Tile::delItem(int qty, int type)
{
    auto& itemVec = this->_items[type];
    for (int i = 0; i < qty && !itemVec.empty(); ++i)
        itemVec.pop_back();
    this->_qty[type] -= qty;
}

void gui::Tile::displayTile(std::map<std::string, int> itemDisplay) const
{
    for (const auto& type: this->_items) {
        for (const auto& item: type) {
            DrawModel(*item->getModel(), item->getPosition(), item->getScale(), item->getColor()); // ask if bad practice
        }
    }


    Vector3 position = {(float)this->_coord.first, 0, (float)this->_coord.second};
    DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});
    DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
}

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

    addItem(qty[FOOD], FOOD);
    addItem(qty[LINEMATE], LINEMATE);
    addItem(qty[DERAUMERE], DERAUMERE);
    addItem(qty[SIBUR], SIBUR);
    addItem(qty[MENDIANE], MENDIANE);
    addItem(qty[PHIRAS], PHIRAS);
    addItem(qty[THYSTAME], THYSTAME);
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
        _items[type].emplace_back(it->second());
    _qty[type] += qty;
}


void gui::Tile::delItem(int qty, int type)
{
    auto& itemVec = _items[type];
    for (int i = 0; i < qty && !itemVec.empty(); ++i)
        itemVec.pop_back();
    _qty[type] -= qty;
}

void gui::Tile::displayTile(std::vector<int> displayItem)
{
    int eltType = FOOD;

    for (const auto& type: _items) {
        for (const auto& item: type) {
            if (displayItem[eltType] == 1)
                DrawModel(*item->getModel(), item->getPosition(), item->getScale(), item->getColor()); // ask if bad practice
        }
        ++eltType;
    }


    Vector3 position = {(float)_coord.first, 0, (float)_coord.second};
    DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});
    DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
}

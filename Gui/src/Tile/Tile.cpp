/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile.cpp
*/

#include "Tile.hpp"
#include "Logger.hpp"

#include <functional>
#include <utility>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::Tile::Tile(std::pair<int, int> coord, std::vector<int> qty, std::vector<std::shared_ptr<Model>> model,
                std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> players,
                std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> eggs,
                std::vector<std::string> teams, int screenWidth, int screenHeight)
    : _isSelected(false), _qty(qty), _coord(std::move(coord)), _teams(std::move(teams)), _models(std::move(model)), _items(7), _eggs(std::move(eggs)), _players(std::move(players)),
    _fontSize(30), _bounds({0, static_cast<float>(screenHeight) * 0.8f, static_cast<float>(screenWidth), static_cast<float>(screenHeight) / 5.0f})

{
    addItem(qty[FOOD], FOOD);
    addItem(qty[LINEMATE], LINEMATE);
    addItem(qty[DERAUMERE], DERAUMERE);
    addItem(qty[SIBUR], SIBUR);
    addItem(qty[MENDIANE], MENDIANE);
    addItem(qty[PHIRAS], PHIRAS);
    addItem(qty[THYSTAME], THYSTAME);

    _itemsText = std::vector<std::pair<std::string, Color>> {
        {"Food", BROWN},
        {"Linemate", YELLOW},
        {"Deraumere", GREEN},
        {"Sibur", RED},
        {"Mendiane", WHITE},
        {"Phiras", BLUE},
        {"Thystame", PURPLE}
    };
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
            if (displayItem[eltType] == 1) {
                DrawModelEx(*item->getModel(), item->getPosition(), Vector3{0, 1, 0}, item->getRotationY(), {item->getScale(), item->getScale(), item->getScale()}, item->getColor());
            }
        }
        ++eltType;
    }
    Vector3 position = {(float)_coord.first, 0, (float)_coord.second};
    if (_isSelected)
        DrawCube(position, 1.0f, 1.0f, 1.0f, {11, 60, 0, 255});
    else
        DrawCube(position, 1.0f, 1.0f, 1.0f, {61, 110, 49, 255});

    DrawCubeWires(position, 1.0f, 1.0f, 1.0f, {61, 0, 49, 255});
}

void gui::Tile::handleUserInput(Camera camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_SHIFT)) {
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        BoundingBox box = {
            { static_cast<float>(_coord.first - 0.5), 0.5, static_cast<float>(_coord.second - 0.5)},
            { static_cast<float>(_coord.first + 0.5), 0.5, static_cast<float>(_coord.second + 0.5)}
        };
        RayCollision collision = GetRayCollisionBox(ray, box);
        if (collision.hit) {
            _isSelected = true;
        } else {
           _isSelected = false;
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsKeyDown(KEY_LEFT_SHIFT)) {
        _isSelected = false;
    }
}

void gui::Tile::displayContent()
{
    if (_isSelected) {
        DrawRectangleRec(_bounds, {255, 255, 255, 50});
        DrawRectangleLinesEx(_bounds, 2, BLACK);

        std::string string = "Tile : " + std::to_string(_coord.first) + "/" + std::to_string(_coord.second);
        DrawText(string.c_str(), _bounds.x + 10, _bounds.y + 10, _fontSize, BLACK);

        float itemWidth = _bounds.width / static_cast<float>(_items.size());
        for (int i = 0; i < static_cast<int>(_itemsText.size()); ++i) {
            Debug::InfoLog("[GUI] Drawing inventory item: " + _itemsText.at(i).first + " with quantity: " + std::to_string(_qty.at(i)));
            std::string text = _itemsText.at(i).first + ": " + std::to_string(_qty.at(i) / 2);
            Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), _fontSize, 1);
            float textX = _bounds.x + i * itemWidth + (itemWidth - textSize.x) / 2;
            float textY = _bounds.y + (_bounds.height - textSize.y) / 2;
            DrawText(text.c_str(), static_cast<int>(textX), static_cast<int>(textY), _fontSize, _itemsText.at(i).second);
        }
    }
}

int gui::Tile::getItem(int type) const
{
    if (type < 0 || type >= (int)_qty.size())
        return 0;
    return _qty[type];
}

std::pair<int, int> gui::Tile::getCoord()
{
    return _coord;
}

std::vector<int> gui::Tile::getPlayersOnTile()
{
    std::vector<int> list;

    for (int i = 0; i < (int) _players->size(); ++i) {
        std::shared_ptr<gui::Player> entity = _players->at(i);

        Vector3 vectorThreePosition = entity->getPosition();
        std::pair<int, int> pairPosition = {vectorThreePosition.x, vectorThreePosition.z};

        if (pairPosition == _coord)
            list.push_back(i);
    }
    return list;
}

std::vector<int> gui::Tile::getEggOnTile()
{
    std::vector<int> list;

    for (int i = 0; i < (int) _eggs->size(); ++i) {
        std::shared_ptr<gui::Egg> entity = _eggs->at(i);

        Vector3 vectorThreePosition = entity->getPosition();
        std::pair<int, int> pairPosition = {vectorThreePosition.x, vectorThreePosition.z};

        if (pairPosition == _coord)
            list.push_back(i);
    }
    return list;
}

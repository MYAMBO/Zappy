/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Client.cpp
*/

#include "Client.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/

gui::Client::Client() : _socket(), _serverAddr(), _Players(), _models(), _teams()
{
    this->_models.emplace_back(safeModelLoader("assets/food/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/linemate/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/deraumere/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/sibur/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/mendiane/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/phiras/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/thystame/scene.gltf"));
}

gui::Client::~Client() = default;

gui::Client& gui::Client::getInstance()
{
    static Client instance;
    return instance;
}

/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void gui::Client::sendCommand(const std::string& command) const
{
    send(this->_socket, command.c_str(), command.size(), 0);
}

void gui::Client::catchCommand()
{
    char buffer[1024];
    while (true) {
        ssize_t bytesReceived = recv(this->_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            std::cout << "Server disconnected.\n";
            break;
        }
        buffer[bytesReceived] = '\0';
        std::cout << "Received from server: " << buffer << "\n";
    }
}

// Get map content
void gui::Client::bct(const std::string& string)
{
    std::vector<std::string> list;
    std::pair<int, int> coord;
    std::vector<int> quantity;

    list = gui::Client::splitString(string);

    if (list.size() != 10)
        throw Error("Command with the wrong number of argument.");

    coord.first = atoi(list[1].c_str());
    coord.first = atoi(list[2].c_str());
    for (int i = 3; i < 9 && i < list.size(); ++i)
        quantity.push_back(atoi(list[i].c_str()));

    if (coord.first && coord.second && quantity.size() == 7)
        this->_Map.emplace_back(std::make_shared<Tile>(coord, quantity, this->_models));
    else
        throw Error("There is a wrong value for creating Tile.");
}

// Get map size
std::pair<int, int> gui::Client::msz() const
{
    static std::pair<int, int> coord;
    char buffer[1024];
    std::vector<std::string> list;

    if (coord.first && coord.second) {
        return coord;
    } else {
        this->sendCommand("msz\n");

        recv(this->_socket, buffer, sizeof(buffer) - 1, 0);
        list = gui::Client::splitString(buffer);

        if (list.size() != 3)
            throw Error("Command with the wrong number of argument.");

        if (list[0] != "msz")
            throw Error("Received an unexpected argument.");

        coord.first = atoi(list[1].c_str());
        coord.second = atoi(list[2].c_str());

        if (coord.first && coord.second && coord.first > 0 && coord.second > 0)
            return coord;
        throw Error("Value for Map size is invalid.");
    }
}

// Name of team
void gui::Client::tna(std::string string)
{
    std::string team_name;
    std::vector<std::string> list = this->splitString(string);

    if (list.size() != 2)
        throw Error("Value for team name is invalid.");
    team_name = list[1];
    if (team_name[team_name.length() - 1] == '\n')
        team_name[team_name.length() - 1] = '\0';

    if (std::find(this->_teams.begin(), this->_teams.end(), team_name) != this->_teams.end())
        // throw error message
        return;

    this->_teams.push_back(team_name);
}

// New Player
void gui::Client::pnw(const std::string& string)
{
    std::vector<std::string> list = splitString(string);

    if (list.size() != 7) {
        // throw
        return;
    }

    std::pair<int, int> coord = msz();

    int id = atoi(list[1].c_str());
    int x = atoi(list[2].c_str());
    int y = atoi(list[3].c_str());
    std::pair<int, int> position;
    position.first = x;
    position.second = y;
    int orientation = atoi(list[4].c_str());
    int level = atoi(list[5].c_str());
    std::string team_name = list[6];

    if (this->findPlayer(id) != -1)
        throw Error("This Id is already used by an other player.");

    if ( id >= 0 && x >= 0 && x < coord.first && y >= 0 && y < coord.second &&
        orientation > 0 && orientation < 5 && level > 0 && level < 9) {
        this->_Players.push_back( std::make_shared<Player>(gui::Player(id, position, static_cast<Orientation>(orientation), level, list[6])));
    } else {
        throw Error("Player's value are wrong.");
    }
}

// Player's position
void gui::Client::ppo(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;
    int posX = 0;
    int posY = 0;
    int orientation = 0;
    std::pair<int, int> mapSize = msz();

    if (list.size() != 5)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());
    posX = atoi(list[2].c_str());
    posY = atoi(list[3].c_str());
    orientation = atoi(list[4].c_str());

    if (posX < 0 || posX >= mapSize.first || posY < 0 || posY >= mapSize.second)
        throw Error("Player's position out of map");

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (orientation < 1 || orientation > 4)
        throw Error("Player's value are wrong.");
}

// Player's level
void gui::Client::plv(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;
    int level = -1;

    if (list.size() != 3)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());
    level = atoi(list[2].c_str());

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (level < 0)
        throw Error("Player's level can't have negative value");
}

// Payer's inventory
void gui::Client::pin(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;
    int posX = 0;
    int posY = 0;
    std::map<std::string, int> inventory;
    std::pair<int, int> mapSize = msz();

    if (list.size() != 11)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());
    posX = atoi(list[2].c_str());
    posY = atoi(list[3].c_str());
    inventory.emplace("food", atoi(list[4].c_str()));
    inventory.emplace("linemate", atoi(list[5].c_str()));
    inventory.emplace("deraumere", atoi(list[6].c_str()));
    inventory.emplace("sibur", atoi(list[7].c_str()));
    inventory.emplace("mendiane", atoi(list[8].c_str()));
    inventory.emplace("phiras", atoi(list[9].c_str()));
    inventory.emplace("thystame", atoi(list[10].c_str()));

    if (posX < 0 || posX >= mapSize.first || posY < 0 || posY >= mapSize.second)
        throw Error("Player's position out of map");

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");

    for (auto elt = inventory.begin(); elt != inventory.end(); elt++)
        if (elt->second < 0)
            throw Error("Player's inventory can't have negative value");
}

// Expulsion
void gui::Client::pex(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;

    if (list.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].c_str());

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");
}

// Broadcast
void gui::Client::pbc(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;
    std::string message;

    if (list.size() != 3)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].c_str());
    message = list[2];

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");
}

// Start of an incantation
void gui::Client::pic(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int incantationLevel;
    int posX = 0;
    int posY = 0;
    std::pair<int, int> mapSize = msz();
    std::vector<int> playersId;
    int id;

    if (list.size() < 5)
        throw Error("Command with the wrong number of argument.");

    posX = atoi(list[1].c_str());
    posY = atoi(list[2].c_str());
    incantationLevel = atoi(list[3].c_str());

    if (incantationLevel < 1 || incantationLevel > 7)
        throw Error("Incantation level is invalid");

    if ((incantationLevel == 1 && list.size() != 5) ||
        ((incantationLevel == 2 || incantationLevel == 3) && list.size() != 6) ||
        ((incantationLevel == 4 || incantationLevel == 5) && list.size() != 8) ||
        ((incantationLevel == 6 || incantationLevel == 7) && list.size() != 10))
        throw Error("Command with the wrong number of argument.");

    if (posX < 0 || posX >= mapSize.first || posY < 0 || posY >= mapSize.second)
        throw Error("Player's position out of map");

    for (int i = 4; i < list.size(); i++){
        id = atoi(list[i].substr(1).c_str());
        if (id && findPlayer(id) == -1)
            throw Error("No player with this Id.");
        playersId.emplace(id);
    }
}

// End of an incantation
void gui::Client::pie(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int posX = 0;
    int posY = 0;
    std::pair<int, int> mapSize = msz();
    int result;

    if (list.size() != 4)
        throw Error("Command with the wrong number of argument.");

    posX = atoi(list[1].c_str());
    posY = atoi(list[2].c_str());
    result = atoi(list[3].c_str());

    if (posX < 0 || posX >= mapSize.first || posY < 0 || posY >= mapSize.second)
        throw Error("Player's position out of map");
}

// egg laying by the player
void gui::Client::pfk(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;

    if (list.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");
}

// Resource dropping
void gui::Client::pdr(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;
    int nbResources = -1;

    if (list.size() != 3)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());
    nbResources = atoi(list[1].c_str());

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (nbResources < 0)
        Error("Resources can't have negative value");
}

// Resource collecting
void gui::Client::pgt(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;
    int nbResources = -1;

    if (list.size() != 3)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());
    nbResources = atoi(list[1].c_str());

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (nbResources < 0)
        Error("Resources can't have negative value");
}

// Player Death
void gui::Client::pdi(const std::string& string)
{
    std::vector<std::string> list;
    int id;
    int indice;

    list = gui::Client::splitString(string);
    id = atoi(list[1].c_str());

    indice = findPlayer(id);

    if (indice == -1)
        throw Error("No player with this Id.");

    if (id > 0) {
        // replace by an other model
        this->_Players.erase(this->_Players.begin() + findPlayer(id));
    }
}

// an egg was laid by a player
void gui::Client::enw(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int eggId;
    int playerId;
    int posX;
    int posY;
    std::pair<int, int> mapSize = msz();

    if (list.size() != 5)
        throw Error("Command with the wrong number of argument.");

    eggId = atoi(list[1].substr(1).c_str());
    playerId = atoi(list[2].substr(1).c_str());
    posX = atoi(list[3].c_str());
    posY = atoi(list[4].c_str());

    if (posX < 0 || posX >= mapSize.first || posY < 0 || posY >= mapSize.second)
        throw Error("Player's position out of map");

    if (eggId && findPlayer(eggId) == -1)
        throw Error("No player with this Id.");
}

// Player connection for an egg
void gui::Client::ebo(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;

    if (list.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());
}

// death of an egg
void gui::Client::edi(std::string string)
{
    std::vector<std::string> list = this->splitString(string);
    int id;

    if (list.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = atoi(list[1].substr(1).c_str());
}

/************************************************************
**           >>>> STATIC  MEMBER FUNCTIONS   <<<<          **
************************************************************/

std::vector<std::string> gui::Client::splitString(const std::string& string)
{
    std::stringstream ss(string);
    std::string buffer;
    std::vector<std::string> list;

    while (std::getline(ss, buffer, ' '))
        list.push_back(buffer);

    return list;
}

int gui::Client::findPlayer(int id)
{
    for (int i = 0; i < this->_Players.size(); ++i) {
        std::shared_ptr<gui::Player> entity = this->_Players[i];

        if (entity->getId() == id)
            return i;
    }
    return -1;
}

/************************************************************
**                  >>>>    SETTERS   <<<<                 **
************************************************************/

void gui::Client::setPlayers(std::vector<std::shared_ptr<Player>> players)
{
    this->_Players = std::move(players);
}

/************************************************************
**               >>>>   GETTERS   <<<<                     **
************************************************************/

std::shared_ptr<Model> gui::Client::safeModelLoader(const std::string& string)
{
    std::cout << string << std::endl;
    std::shared_ptr<Model> model = std::make_shared<Model>(LoadModel(string.c_str()));

    if (model->meshCount == 0 || model->meshes == nullptr)
        throw gui::FailedLoadModel();

    return model;
}

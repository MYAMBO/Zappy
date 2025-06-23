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
#include <netdb.h>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>

/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/

gui::Client::Client() : _socket(), _isActive(true), _Players(), _models(), _teams()
{
    this->_models.emplace_back(safeModelLoader("assets/food/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/linemate/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/deraumere/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/sibur/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/mendiane/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/phiras/scene.gltf"));
    this->_models.emplace_back(safeModelLoader("assets/thystame/scene.gltf"));

    connectToServer();
}

gui::Client::~Client()
{
    this->_thread.detach();
}

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

void gui::Client::receiveLoop()
{
    std::map<std::string, std::function<void(std::vector<std::string> stringArray)>> funcMap {
        {"msz", [this](const std::vector<std::string>& s) { this->msz(s); }},
        {"bct", [this](const std::vector<std::string>& s) { this->bct(s); }},
        {"tna", [this](const std::vector<std::string>& s) { this->tna(s); }},
        {"pnw", [this](const std::vector<std::string>& s) { this->pnw(s); }},
        {"ppo", [this](const std::vector<std::string>& s) { this->ppo(s); }},
        {"plv", [this](const std::vector<std::string>& s) { this->plv(s); }},
        {"pin", [this](const std::vector<std::string>& s) { this->pin(s); }},
        {"pex", [this](const std::vector<std::string>& s) { this->pex(s); }},
        {"pbc", [this](const std::vector<std::string>& s) { this->pbc(s); }},
        {"pic", [this](const std::vector<std::string>& s) { this->pic(s); }},
        {"pie", [this](const std::vector<std::string>& s) { this->pie(s); }},
        {"pfk", [this](const std::vector<std::string>& s) { this->pfk(s); }},
        {"pdr", [this](const std::vector<std::string>& s) { this->pdr(s); }},
        {"pgt", [this](const std::vector<std::string>& s) { this->pgt(s); }},
        {"pdi", [this](const std::vector<std::string>& s) { this->pdi(s); }},
        {"enw", [this](const std::vector<std::string>& s) { this->enw(s); }},
        {"ebo", [](const std::vector<std::string>& s) { gui::Client::ebo(s); }},
        {"edi", [](const std::vector<std::string>& s) { gui::Client::edi(s); }},
        {"sgt", [](const std::vector<std::string>& s) { gui::Client::sgt(s); }},
        {"sst", [](const std::vector<std::string>& s) { gui::Client::sst(s); }},
        {"seg", [this](const std::vector<std::string>& s) { this->seg(s); }},
        {"smg", [](const std::vector<std::string>& s) { gui::Client::smg(s); }},
        {"suc", [](const std::vector<std::string>& s) { gui::Client::suc(s); }},
        {"sbp", [](const std::vector<std::string>& s) { gui::Client::sbp(s); }}
    };

    char buffer[1024];
    std::vector<std::string> stringArray;
    while (true) {
        ssize_t bytesReceived = recv(this->_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            std::cout << "Server disconnected.\n";
            break;
        }
        buffer[bytesReceived] = '\0';
        stringArray = splitString(buffer);

        if (stringArray[0] == "WELCOME\n")
            continue;

        if (funcMap[stringArray[0]])
            funcMap[stringArray[0]](stringArray);
        else
            throw Error("This protocol don't exist : " + stringArray[0]);
    }
}

void gui::Client::connectToServer()
{
    const char* hostname = "zappy.antoiix.me";
    const char* port = "12345";

    addrinfo hints{}, *res;
    hints.ai_family = AF_INET; // IPV4
    hints.ai_socktype = SOCK_STREAM; // TCP socket

    int status = getaddrinfo(hostname, port, &hints, &res);
    if (status != 0)
        throw Error(gai_strerror(status));

    this->_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (this->_socket < 0) {
        freeaddrinfo(res);
        throw Error("Socket creation failed.\n");
    }

    if (connect(this->_socket, res->ai_addr, res->ai_addrlen) < 0) {
        freeaddrinfo(res);
        close(this->_socket);
        throw  Error("Connection failed.\n");
    }

    freeaddrinfo(res);

    this->_thread = std::thread(&gui::Client::receiveLoop, this);

//    sendCommand("msz\n");
//    sendCommand("mct\n");
//    sendCommand("tna\n");
}

/************************************************************
**               >>>>       COMMANDS       <<<<            **
************************************************************/

// Get map size
void gui::Client::msz(std::vector<std::string> stringArray)
{
    std::pair<int, int> size;

    if (stringArray.size() != 3)
        throw Error("Value for team name is invalid.");

    size.first = std::stoi(stringArray[1]);
    size.second = std::stoi(stringArray[2]);

    if (size.first < 1 || size.second < 1)
        throw Error("Can't have 0 or less map size");

    this->_size = size;
}

// Get map content
void gui::Client::bct(std::vector<std::string> stringArray)
{
    std::pair<int, int> coord;
    std::vector<int> quantity;

    if (stringArray.size() != 10)
        throw Error("Command with the wrong number of argument.");

    coord.first = std::stoi(stringArray[1]);
    coord.second = std::stoi(stringArray[2]);
    for (int i = 3; i < 9 && i < (int)stringArray.size(); ++i)
        quantity.push_back(std::stoi(stringArray[i]));

    if (coord.first && coord.second && quantity.size() == 7)
        this->_Map.emplace_back(std::make_shared<Tile>(coord, quantity, this->_models));
    else
        throw Error("There is a wrong value for creating Tile.");
}

// Name of team
void gui::Client::tna(std::vector<std::string> stringArray)
{
    std::string team_name;

    if (stringArray.size() != 2)
        throw Error("Value for team name is invalid.");
    team_name = stringArray[1];
    if (team_name[team_name.length() - 1] == '\n')
        team_name[team_name.length() - 1] = '\0';

    if (std::find(this->_teams.begin(), this->_teams.end(), team_name) != this->_teams.end())
        throw Error("Team name already exist");

    this->_teams.push_back(team_name);
}

// New Player
void gui::Client::pnw(std::vector<std::string> stringArray)
{

    if (stringArray.size() != 7)
        throw Error("Wrong Number of parameter");

    int id = std::stoi(stringArray[1].substr(1));
    int x = std::stoi(stringArray[2]);
    int y = std::stoi(stringArray[3]);
    std::pair<int, int> position;
    position.first = x;
    position.second = y;
    int orientation = std::stoi(stringArray[4]);
    int level = std::stoi(stringArray[5]);
    std::string team_name = stringArray[6];

    if (this->findPlayer(id) != -1)
        throw Error("This Id is already used by an other player.");

    if ( id >= 0 && x >= 0 && x < this->_size.first && y >= 0 && y < this->_size.second &&
        orientation > 0 && orientation < 5 && level > 0 && level < 9) {
 //       this->_Players.push_back( std::make_shared<Player>(gui::Player(id, position, static_cast<Orientation>(orientation), level, team_name)));
    } else {
        throw Error("Player's value are wrong.");
    }
}

// Player's position
void gui::Client::ppo(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 5)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int posX = std::stoi(stringArray[2]);
    int posY = std::stoi(stringArray[3]);
    int orientation = std::stoi(stringArray[4]);

    if (posX < 0 || posX >= this->_size.first || posY < 0 || posY >= this->_size.second)
        throw Error("Player's position out of map");

    if (findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (orientation < 0 || orientation > 3)
        throw Error("Player's value are wrong.");

    this->_Players[findPlayer(id)]->startMoveTo({(float)posX, 0.5, (float)posY});
}

// Player's level
void gui::Client::plv(std::vector<std::string> stringArray)
{


    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int level = std::stoi(stringArray[2]);

    if (findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (level < 0)
        throw Error("Player's level can't have negative value");

    this->_Players[findPlayer(id)]->setLevel(level);
}

// Payer's inventory
void gui::Client::pin(std::vector<std::string> stringArray)
{
    std::map<std::string, int> inventory;

    if (stringArray.size() != 11)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int posX = std::stoi(stringArray[2]);
    int posY = std::stoi(stringArray[3]);
    inventory.emplace("food", std::stoi(stringArray[4]));
    inventory.emplace("linemate", std::stoi(stringArray[5]));
    inventory.emplace("deraumere", std::stoi(stringArray[6]));
    inventory.emplace("sibur", std::stoi(stringArray[7]));
    inventory.emplace("mendiane", std::stoi(stringArray[8]));
    inventory.emplace("phiras", std::stoi(stringArray[9]));
    inventory.emplace("thystame", std::stoi(stringArray[10]));

    if (posX < 0 || posX >= this->_size.first || posY < 0 || posY >= this->_size.second)
        throw Error("Player's position out of map");

    if (findPlayer(id) == -1)
        throw Error("No player with this Id.");

    for (auto & elt : inventory)
        if (elt.second < 0)
            throw Error("Player's inventory can't have negative value");

    for (auto & item : inventory)
        this->_Players[findPlayer(id)]->getInventory().setInventoryItem(item.first, item.second);
}

// Expulsion
void gui::Client::pex(std::vector<std::string> stringArray)
{

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");
}

// Broadcast
void gui::Client::pbc(std::vector<std::string> stringArray)
{

    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    std::string message = stringArray[2];

    if (findPlayer(id) == -1)
        throw Error("No player with this Id.");

    this->_Players[findPlayer(id)]->broadcastAnimation();
}

// Start of an incantation
void gui::Client::pic(std::vector<std::string> stringArray)
{
    std::vector<int> playersId;

    if (stringArray.size() < 5)
        throw Error("Command with the wrong number of argument.");

    int posX = std::stoi(stringArray[1]);
    int posY = std::stoi(stringArray[2]);
    int incantationLevel = std::stoi(stringArray[3]);
    int id;

    if (incantationLevel < 1 || incantationLevel > 7)
        throw Error("Incantation level is invalid");

    if ((incantationLevel == 1 && stringArray.size() != 5) ||
        ((incantationLevel == 2 || incantationLevel == 3) && stringArray.size() != 6) ||
        ((incantationLevel == 4 || incantationLevel == 5) && stringArray.size() != 8) ||
        ((incantationLevel == 6 || incantationLevel == 7) && stringArray.size() != 10))
        throw Error("Command with the wrong number of argument.");

    if (posX < 0 || posX >= this->_size.first || posY < 0 || posY >= this->_size.second)
        throw Error("Player's position out of map");

    for (int i = 4; i < (int)stringArray.size(); i++){
        id = std::stoi(stringArray[i].substr(1));
        if (id && findPlayer(id) == -1)
            throw Error("No player with this Id.");
//        playersId.emplace(id);
    }
}

// End of an incantation
void gui::Client::pie(std::vector<std::string> stringArray) const
{
    int posX = 0;
    int posY = 0;
    int result;

    if (stringArray.size() != 4)
        throw Error("Command with the wrong number of argument.");

    posX = std::stoi(stringArray[1]);
    posY = std::stoi(stringArray[2]);
    result = std::stoi(stringArray[3]);

    if (posX < 0 || posX >= this->_size.first || posY < 0 || posY >= this->_size.second)
        throw Error("Player's position out of map");
    std::cout << "in pie " << result << std::endl;
}

// egg laying by the player
void gui::Client::pfk(std::vector<std::string> stringArray)
{
    int id;

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = std::stoi(stringArray[1].substr(1));

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");
}

// Resource dropping
void gui::Client::pdr(std::vector<std::string> stringArray)
{

    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int nbResources = std::stoi(stringArray[2]);

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (nbResources < 0)
        throw Error("Resources can't have negative value");

    // get Player and remove item
    // addItem on Tile
}

// Resource collecting
void gui::Client::pgt(std::vector<std::string> stringArray)
{
    int id;
    int nbResources;

    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");

    id = std::stoi(stringArray[1].substr(1));
    nbResources = std::stoi(stringArray[2]);

    if (id && findPlayer(id) == -1)
        throw Error("No player with this Id.");

    if (nbResources < 0)
        throw Error("Resources can't have negative value");

    // get Player and add item
    // removeItem on Tile
}

// Player Death
void gui::Client::pdi(std::vector<std::string> stringArray)
{
    int id = std::stoi(stringArray[1].substr(1));

    int indice = findPlayer(id);

    if (indice == -1)
        throw Error("No player with this Id.");

    if (id > 0) {
        // replace by an other model
        this->_Players.erase(this->_Players.begin() + findPlayer(id));
    }
}

// a player laid an egg
void gui::Client::enw(std::vector<std::string> stringArray)
{
    int eggId;
    int playerId;
    int posX;
    int posY;

    if (stringArray.size() != 5)
        throw Error("Command with the wrong number of argument.");

    eggId = std::stoi(stringArray[1].substr(1));
    playerId = std::stoi(stringArray[2].substr(1));
    posX = std::stoi(stringArray[3]);
    posY = std::stoi(stringArray[4]);

    if (posX < 0 || posX >= this->_size.first || posY < 0 || posY >= this->_size.second)
        throw Error("Player's position out of map");

    if (eggId && findPlayer(eggId) == -1)
        throw Error("No player with this Id.");
    std::cout << "in enw " << playerId << std::endl;
}

// Player connection for an egg
void gui::Client::ebo(std::vector<std::string> stringArray)
{
    int id;

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = std::stoi(stringArray[1].substr(1));

    std::cout << "in ebo " << id << std::endl;
}

// death of an egg
void gui::Client::edi(std::vector<std::string> stringArray)
{
    int id;

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = std::stoi(stringArray[1].substr(1));

    std::cout << "in edi " << id << std::endl;
}

// time unit request
void gui::Client::sgt(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    int time_unit = std::stoi(stringArray[1]);

    std::cout << "in sgt " << time_unit << std::endl;
}

// time unit modification
void gui::Client::sst(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    int time_unit = std::stoi(stringArray[1]);

    std::cout << "in sst " << time_unit << std::endl;
}

// end of game
void gui::Client::seg(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    std::string winner = stringArray[1];

    this->_isActive = false;
}

// message from the server
void gui::Client::smg(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    std::string message = stringArray[1];
}

// unknown command
void gui::Client::suc(const std::vector<std::string>& stringArray)
{
    if (stringArray.size() != 1)
        throw Error("Wrong number of parameter.");
}

// command parameter
void gui::Client::sbp(const std::vector<std::string>& stringArray)
{
    if (stringArray.size() != 1)
        throw Error("Wrong number of parameter.");
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
    for (int i = 0; i < (int)this->_Players.size(); ++i) {
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

void gui::Client::setMap(std::vector<std::shared_ptr<gui::Tile>> map)
{
    this->_Map = std::move(map);
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

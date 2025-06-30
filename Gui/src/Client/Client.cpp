/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Client.cpp
*/

#include "Error.hpp"
#include "Client.hpp"
#include "Logger.hpp"

#include <netdb.h>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include <sys/socket.h>


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/
gui::Client::Client(std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> players, std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> map,
        std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> eggs, const std::shared_ptr<Camera>& camera, const std::shared_ptr<CamState>& camState,
        std::shared_ptr<std::vector<std::shared_ptr<Model>>> models, const std::shared_ptr<Display>& display, const std::shared_ptr<int>& timeUnit,
        std::shared_ptr<std::string> hostname = std::make_shared<std::string>("localhost"), std::shared_ptr<std::string> port = std::make_shared<std::string>("12345"))
    : _mutex(), _camera(camera), _camState(camState), _previousPort(port->c_str()), _previousHostname(hostname->c_str()),_hostname(std::move(hostname)), _port(std::move(port)),
      _socket(), _isActive(), _thread(), _size(), _timeUnit(timeUnit), _display(display),
      _displayTeams(), _teams(std::make_shared<std::vector<std::string>>()), _teamColors(std::make_shared<std::map<std::string, Color>>()), _models(std::move(models)),
      _eggs(std::move(eggs)), _map(std::move(map)), _players(std::move(players))
{
    _displayTeams = std::make_shared<TeamsDisplay>(_teams, _teamColors, _eggs, _players);
    _display = display;
    _display->setTeams(_teams);
    _display->setTeamsColors(_teamColors);
    _display->setDisplayTeams(_displayTeams);
    _camera = camera;
    _camState = camState;
    _timeUnit = timeUnit;
    connectToServer();
}

gui::Client::~Client()
{
    _socket.close();
    if (_thread.joinable()) {
        _thread.join();
    }
}

/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void gui::Client::sendCommand(const std::string& command)
{
    _socket.send(command);
    Debug::InfoLog("Sent command: " + command);
}

void gui::Client::receiveLoop()
{
    std::map<std::string, std::function<void(std::vector<std::string> stringArray)>> funcMap {
        {"msz", [this](const std::vector<std::string>& s) { msz(s); }},
        {"bct", [this](const std::vector<std::string>& s) { bct(s); }},
        {"tna", [this](const std::vector<std::string>& s) { tna(s); }},
        {"pnw", [this](const std::vector<std::string>& s) { pnw(s); }},
        {"ppo", [this](const std::vector<std::string>& s) { ppo(s); }},
        {"plv", [this](const std::vector<std::string>& s) { plv(s); }},
        {"pin", [this](const std::vector<std::string>& s) { pin(s); }},
        {"pex", [this](const std::vector<std::string>& s) { pex(s); }},
        {"pbc", [this](const std::vector<std::string>& s) { pbc(s); }},
        {"pic", [this](const std::vector<std::string>& s) { pic(s); }},
        {"pie", [this](const std::vector<std::string>& s) { pie(s); }},
        {"pfk", [this](const std::vector<std::string>& s) { pfk(s); }},
        {"pdr", [this](const std::vector<std::string>& s) { pdr(s); }},
        {"pgt", [this](const std::vector<std::string>& s) { pgt(s); }},
        {"pdi", [this](const std::vector<std::string>& s) { pdi(s); }},
        {"enw", [this](const std::vector<std::string>& s) { enw(s); }},
        {"ebo", [this](const std::vector<std::string>& s) { ebo(s); }},
        {"edi", [this](const std::vector<std::string>& s) { edi(s); }},
        {"sgt", [this](const std::vector<std::string>& s) { sgt(s); }},
        {"sst", [this](const std::vector<std::string>& s) { sst(s); }},
        {"seg", [this](const std::vector<std::string>& s) { seg(s); }},
        {"smg", [this](const std::vector<std::string>& s) { smg(s); }},
        {"suc", [this](const std::vector<std::string>& s) { suc(s); }},
        {"sbp", [this](const std::vector<std::string>& s) { sbp(s); }}
    };
    std::string incompleteCommand;
    std::vector<std::string> stringArray;
    
    int loopCountSelect = 0;
    while (_socket.isConnected()) {

        loopCountSelect++;
        for (size_t i = 0; i < _players->size(); ++i) {
            if (_players->at(i)->getSelected() && loopCountSelect >= 60) {
                sendCommand("pin #" + std::to_string(_players->at(i)->getId()) + "\n");
                loopCountSelect = 0;
            }
        }

        constexpr size_t BUFFER_SIZE = 4096;
        std::vector<char> buffer(BUFFER_SIZE);
        
        ssize_t bytesReceived = _socket.receive(buffer.data(), buffer.size() - 1, true);
        
        if (bytesReceived < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            } else {
                break;
            }
        }
        if (bytesReceived == 0) {
            std::cout << "Server disconnected.\n";
            break;
        }

        buffer[bytesReceived] = '\0';
        std::string receivedData(buffer.data(), bytesReceived);
        std::string completeData = incompleteCommand + receivedData;
        incompleteCommand.clear();

        auto commands = splitString(completeData, '\n');
        if (!completeData.empty() && completeData.back() != '\n') {
            if (!commands.empty()) {
                incompleteCommand = commands.back();
                commands.pop_back();
            }
        }
        
        for (const auto &command : commands) {
            Debug::InfoLog("Received command: " + command);
            if (command.empty()) continue;

            stringArray = splitString(command, ' ');
            if (stringArray.empty()) continue;

            if (stringArray[0] == "WELCOME" ||
                stringArray[0] == "GRAPHIC" ||
                stringArray[0] == "ko") {
                continue;
            }

            auto it = funcMap.find(stringArray[0]);
            if (it != funcMap.end()) {
                try {
                    it->second(stringArray);
                } catch (const std::exception &e) {
                    Debug::WarningLog(e.what());
                }
            } else {
                Debug::DebugLog("Unknown command received: " + stringArray[0]);
            }
        }
    }
}

void gui::Client::connectToServer()
{
    _socket.connect(this->_hostname->c_str(), this->_port->c_str());

    _thread = std::thread(&gui::Client::receiveLoop, this);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    sendCommand("GRAPHIC\n");
    sendCommand("msz\n");
    sendCommand("mct\n");
    sendCommand("tna\n");
    sendCommand("sgt\n");
}

void gui::Client::newServerConnection()
{
    if (_previousHostname == _hostname->c_str() && _previousPort == _port->c_str())
        return;
    else {
        _socket.close();
        _thread.join();
        _players->clear();
        _eggs->clear();
        _map->clear();
        _teams->clear();
        _teamColors->clear();

        _previousHostname = _hostname->c_str();
        _previousPort = _port->c_str();
        connectToServer();
    }
}

/************************************************************
**               >>>>       COMMANDS       <<<<            **
************************************************************/


/*               >>>>       MAP SIZE       <<<<            */

void gui::Client::msz(std::vector<std::string> stringArray)
{
    std::pair<int, int> size;

    if (stringArray.size() != 3)
        throw Error("Value for team name is invalid.");

    size.first = std::stoi(stringArray[1]);
    size.second = std::stoi(stringArray[2]);

    if (size.first < 1 || size.second < 1)
        throw Error("Can't have 0 or less map size");

    std::lock_guard<std::mutex> lock(_mutex);

    _size = size;
}


/*               >>>>       TILE CONTENT       <<<<            */

void gui::Client::bct(std::vector<std::string> stringArray)
{
    std::pair<int, int> coord;
    std::vector<int> quantity;

    if (stringArray.size() != 10)
        throw Error("Command with the wrong number of argument.");
    coord.first = std::stoi(stringArray[1]);
    coord.second = std::stoi(stringArray[2]);

    for (int i = 3; i <= 9 && i < (int)stringArray.size(); ++i) {
        quantity.push_back(std::stoi(stringArray[i]));
    }

    std::lock_guard<std::mutex> lock(_mutex);

    if (coord.first >= 0 && coord.first <= _size.first && coord.second >= 0 && coord.first <= _size.second
        && quantity.size() == 7 && findTile(coord.first, coord.second) == -1) {
        _map->emplace_back(std::make_shared<Tile>(coord, quantity, _models, SCREEN_WIDTH, SCREEN_HEIGHT, _displayTeams));
        return;
    } else if (findTile(coord.first, coord.second) != -1) {
        auto &_tile = _map->at(findTile(coord.first, coord.second));
        for (int i = 0; i < 7; ++i) {
            while (quantity[i] > _tile->getItem(i)) {
                _tile->addItem(1, i);
            }
            while (quantity[i] < _tile->getItem(i)) {
                _tile->delItem(1, i);
            }
        }
    } else {
        throw Error("Tile's value are wrong.");
    }
}


/*               >>>>       TEAM NAMES       <<<<            */

void gui::Client::tna(std::vector<std::string> stringArray)
{
    std::string team_name;

    if (stringArray.size() != 2)
        throw Error("Value for team name is invalid.");
    team_name = stringArray[1];
    if (team_name[team_name.length() - 1] == '\n')
        team_name[team_name.length() - 1] = '\0';

    for (int i = 0; i < (int)_teams->size(); ++i) {
        if (_teams->at(i) == team_name)
            throw Error("Team already exists: " + team_name);
    }

    std::vector <Color> colors = {
        {255, 0, 255, 255}, {0, 255, 255, 255}, {255, 165, 0, 255}, {128, 0, 128, 255},
        {0, 128, 128, 255}, {192, 192, 192, 255}, {255, 20, 147, 255},
        {0, 0, 139, 255}, {0, 100, 0, 255}, {70, 130, 180, 255},
        {255, 105, 180, 255}, {255, 0, 0, 255}, {0, 0, 255, 255},
        {0, 128, 0, 255}, {128, 128, 0, 255}, {128, 128, 128, 255}
    };

    std::lock_guard<std::mutex> lock(_mutex);

    _teams->push_back(team_name);
    if (_teams->size() > colors.size()) {
        _teamColors->operator[](team_name) = {255, 255, 255, 255};
        return;
    }
    _teamColors->operator[](team_name) = colors[_teams->size()];
}


/*               >>>>       NEW PLAYER       <<<<            */

void gui::Client::pnw(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 7)
        throw Error("Wrong Number of parameter");

    int id = std::stoi(stringArray[1].substr(1));
    int x = std::stoi(stringArray[2]);
    int y = std::stoi(stringArray[3]);
    std::pair<int, int> position(x, y);
    int orientation = std::stoi(stringArray[4]);
    int level = std::stoi(stringArray[5]);
    std::string team_name = stringArray[6];

    if (findPlayer(id) != -1)
        throw Error("This Id is already used by an other player.");

    std::lock_guard<std::mutex> lock(_mutex);

    if (id >= 0 && x >= 0 && x < _size.first && y >= 0 && y < _size.second &&
        orientation > 0 && orientation < 5 && level > 0 && level < 9) {
        _display->addPlayer(id, position, static_cast<Orientation>(orientation), level, team_name);
        auto player = _players->at(findPlayer(id));
        if (player->getId() == id)
            player->setColorTeam(_teamColors);
    } else
        throw Error("Player's value are wrong.");
}


/*               >>>>       PLAYER POSITION       <<<<            */

void gui::Client::ppo(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 5)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int posX = std::stoi(stringArray[2]);
    int posY = std::stoi(stringArray[3]);
    int orientation = std::stoi(stringArray[4]);

    if (posX < 0 || posX >= _size.first || posY < 0 || posY >= _size.second)
        throw Error("Player's position out of map");

    if (findPlayer(id) == -1)
        return;

    if (orientation <= 0 || orientation >= 5)
        throw Error("Player's value are wrong.");
    
    std::lock_guard<std::mutex> lock(_mutex);

    _players->at(findPlayer(id))->setOrientation(static_cast<Orientation>(orientation));
    if (_players->at(findPlayer(id))->getPushed()) {
        _players->at(findPlayer(id))->setPosition({(float)posX, 1, (float)posY});
        _players->at(findPlayer(id))->setPushed(false);
        return;
    }
    _players->at(findPlayer(id))->startMoveTo({(float)posX, 1, (float)posY});
}


/*               >>>>       PLAYER LEVEL       <<<<            */

void gui::Client::plv(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int level = std::stoi(stringArray[2]);

    if (findPlayer(id) == -1)
        return;

    if (level < 0)
        throw Error("Player's level can't have negative value");

    std::lock_guard<std::mutex> lock(_mutex);

    _players->at(findPlayer(id))->setLevel(level);
}


/*               >>>>       PLAYER INVENTORY       <<<<            */

void gui::Client::pin(std::vector<std::string> stringArray)
{
    std::map<std::string, int> inventory;

    if (stringArray.size() != 11)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int posX = std::stoi(stringArray[2]);
    int posY = std::stoi(stringArray[3]);
    inventory.emplace("Food", std::stoi(stringArray[4]));
    inventory.emplace("Linemate", std::stoi(stringArray[5]));
    inventory.emplace("Deraumere", std::stoi(stringArray[6]));
    inventory.emplace("Sibur", std::stoi(stringArray[7]));
    inventory.emplace("Mendiane", std::stoi(stringArray[8]));
    inventory.emplace("Phiras", std::stoi(stringArray[9]));
    inventory.emplace("Thystame", std::stoi(stringArray[10]));

    if (posX < 0 || posX >= _size.first || posY < 0 || posY >= _size.second)
        throw Error("Player's position out of map");

    if (findPlayer(id) == -1)
        return;

    for (auto & elt : inventory)
        if (elt.second < 0)
            throw Error("Player's inventory can't have negative value");

    std::lock_guard<std::mutex> lock(_mutex);

    Debug::InfoLog("[GUI] Set inventory for player ID: " + std::to_string(id) + "\n");
    for (auto & item : inventory) {
        _players->at(findPlayer(id))->setInventory(item.first, item.second);
    }
}


/*               >>>>       EJECT       <<<<            */

void gui::Client::pex(std::vector<std::string> stringArray)
{

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));

    if (id && findPlayer(id) == -1)
        return;

    std::string command;

    std::lock_guard<std::mutex> lock(_mutex);

    for (size_t i = 0; i < _players->size() ; ++i) {
        if (_players->at(i)->getPosition().x == _players->at(findPlayer(id))->getPosition().x &&
            _players->at(i)->getPosition().y == _players->at(findPlayer(id))->getPosition().y) {
            _players->at(i)->setPushed(true);
        }
    }
    for (size_t i = 0; i < _players->size() ; ++i) {
        command = "ppo #" + std::to_string(_players->at(i)->getId()) + "\n";
        sendCommand(command);
    }
}


/*               >>>>       BROADCAST       <<<<            */

void gui::Client::pbc(std::vector<std::string> stringArray)
{

    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    std::string message = stringArray[2];

    if (findPlayer(id) == -1)
        return;
    
    std::lock_guard<std::mutex> lock(_mutex);

    _players->at(findPlayer(id))->setBroadcasting(true);
}


/*               >>>>       START INCANTATION       <<<<            */

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

    if (posX < 0 || posX >= _size.first || posY < 0 || posY >= _size.second)
        throw Error("Player's position out of map");

    std::lock_guard<std::mutex> lock(_mutex);

    for (int i = 4; i < (int)stringArray.size(); i++){
        id = std::stoi(stringArray[i].substr(1));
        if (id && findPlayer(id) == -1)
            return;
        _players->at(findPlayer(id))->setIncantation(true);
    }
}


/*               >>>>       END INCANTATION       <<<<            */

void gui::Client::pie(std::vector<std::string> stringArray)
{
    int posX = 0;
    int posY = 0;
    int result;

    if (stringArray.size() != 4)
        throw Error("Command with the wrong number of argument.");

    posX = std::stoi(stringArray[1]);
    posY = std::stoi(stringArray[2]);
    result = std::stoi(stringArray[3]);

    if (posX < 0 || posX >= _size.first || posY < 0 || posY >= _size.second)
        throw Error("Player's position out of map");
    if (result < 0 || result > 8)
        throw Error("Incantation result is invalid");

    std::lock_guard<std::mutex> lock(_mutex);

    for (size_t i = 0; i < _players->size(); ++i) {
        auto &player = _players->at(i);
        if (player->getPosition().x == posX && player->getPosition().y == posY) {
            player->setIncantationEnded(true);
            sendCommand("plv #" + std::to_string(player->getId()) + "\n");
        }
    }
}


/*               >>>>       EGG LAYING       <<<<            */

void gui::Client::pfk(std::vector<std::string> stringArray)
{
    int id;

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = std::stoi(stringArray[1].substr(1));

    if (id && findPlayer(id) == -1)
        return;
}


/*               >>>>       RESSOURCE DROP       <<<<            */

void gui::Client::pdr(std::vector<std::string> stringArray)
{

    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");

    int id = std::stoi(stringArray[1].substr(1));
    int nbResources = std::stoi(stringArray[2]);

    if (id && findPlayer(id) == -1)
        return;

    if (nbResources < 0)
        throw Error("Resources can't have negative value");

    std::lock_guard<std::mutex> lock(_mutex);

    auto &player = _players->at(findPlayer(id));
    auto position = player->getPosition();
    size_t index = position.x * _size.first + position.y;
    auto &tile = _map->at(index);

    if (tile->getItem(nbResources) > 0) {
        tile->addItem(1, nbResources);
        sendCommand("pin #" + std::to_string(id) +"\n");
    }
}


/*               >>>>       RESSOURCE COLLECT       <<<<            */

void gui::Client::pgt(std::vector<std::string> stringArray)
{
    int id;
    int nbResources;
    std::map<int, std::string> resources;

    if (stringArray.size() != 3)
        throw Error("Command with the wrong number of argument.");
    id = std::stoi(stringArray[1].substr(1));
    nbResources = std::stoi(stringArray[2]);

    if (id && findPlayer(id) == -1)
        return;

    if (nbResources < 0)
        throw Error("Resources can't have negative value");

    std::lock_guard<std::mutex> lock(_mutex);

    auto &player = _players->at(findPlayer(id));
    auto position = player->getPosition();
    size_t index = position.x * _size.first + position.y;
    auto &tile = _map->at(index);

    if (tile->getItem(nbResources) > 0) {
        tile->delItem(1, nbResources);
        sendCommand("pin #" + std::to_string(id) +"\n");
    }
}


/*               >>>>       PLAYER DEATH       <<<<            */

void gui::Client::pdi(std::vector<std::string> stringArray)
{
    int id = std::stoi(stringArray[1].substr(1));

    int indice = findPlayer(id);

    if (indice == -1)
        return;

    std::lock_guard<std::mutex> lock(_mutex);

    if (id > 0) {
        _players->at(indice)->setisDead(true);
    }
}


/*               >>>>       LAID EGG       <<<<            */

void gui::Client::enw(std::vector<std::string> stringArray)
{
    int playerIndice;
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

    if (posX < 0 || posX >= _size.first || posY < 0 || posY >= _size.second)
        throw Error("Player's position out of map");

    std::lock_guard<std::mutex> lock(_mutex);

    playerIndice = findPlayer(eggId);

    if (playerId == -1)
        _eggs->emplace_back(std::make_shared<gui::Egg>(eggId, std::make_pair(posX, posY), _display->_eggModel, ""));
    else
        _eggs->emplace_back(std::make_shared<gui::Egg>(eggId, std::make_pair(posX, posY), _display->_eggModel, _players->at(playerIndice)->getTeam()));
}


/*               >>>>       CONNECT EGG       <<<<            */

void gui::Client::ebo(std::vector<std::string> stringArray)
{
    int id;

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = std::stoi(stringArray[1].substr(1));

    std::lock_guard<std::mutex> lock(_mutex);

    int indice = findEgg(id);

    if (indice != -1)
        _eggs->erase(_eggs->begin() + indice);
    else
        throw Error("Invalid Egg Id");
}


/*               >>>>       DEATH EGG       <<<<            */

void gui::Client::edi(std::vector<std::string> stringArray)
{
    int id;

    if (stringArray.size() != 2)
        throw Error("Command with the wrong number of argument.");

    id = std::stoi(stringArray[1].substr(1));

    std::lock_guard<std::mutex> lock(_mutex);

    int indice = findEgg(id);

    if (indice != -1)
        _eggs->erase(_eggs->begin() + indice);
    else
        throw Error("Invalid Egg Id");
}


/*               >>>>       TIME REQUEST       <<<<            */

void gui::Client::sgt(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    int time_unit = std::stoi(stringArray[1]);

    std::lock_guard<std::mutex> lock(_mutex);

    _timeUnit = std::make_shared<int>(time_unit);
    Debug::InfoLog("[GUI] Time unit set to: " + std::to_string(time_unit));
}


/*               >>>>       TIME MODIFICATION       <<<<            */

void gui::Client::sst(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    int time_unit = std::stoi(stringArray[1]);

    std::lock_guard<std::mutex> lock(_mutex);

    _timeUnit = std::make_shared<int>(time_unit);
    Debug::InfoLog("[GUI] Time unit modified to: " + std::to_string(time_unit));
}


/*               >>>>       END OF GAME       <<<<            */

void gui::Client::seg(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    std::string winner = stringArray[1];

    std::lock_guard<std::mutex> lock(_mutex);

    _display->setWinner(winner);
    _isActive = false;
    Debug::InfoLog("[GUI] Game ended. Winner: " + winner);
}


/*               >>>>       MSG FROM SERVER       <<<<            */

void gui::Client::smg(std::vector<std::string> stringArray)
{
    if (stringArray.size() != 2)
        throw Error("Wrong number of parameter.");

    std::string message = stringArray[1];
    Debug::InfoLog("Server message: " + message);
}


/*               >>>>       UNKNOWN COMMAND       <<<<            */

void gui::Client::suc(const std::vector<std::string>& stringArray)
{
    if (stringArray.size() != 1)
        throw Error("Wrong number of parameter.");
    Debug::WarningLog("[GUI] Received command: suc");
}


/*               >>>>       COMMAND PARAMETER       <<<<            */

void gui::Client::sbp(const std::vector<std::string>& stringArray)
{
    if (stringArray.size() != 1)
        throw Error("Wrong number of parameter.");
    Debug::WarningLog("[GUI] Received command: sbp");
}


/************************************************************
 **           >>>>  MEMBER FUNCTIONS   <<<<          **
 ************************************************************/

std::vector<std::string> gui::Client::splitString(const std::string& string, char delimiter)
{
    std::vector<std::string> list;
    std::string buffer;
    bool inQuotes = false;

    for (size_t i = 0; i < string.length(); ++i) {
        char c = string[i];
        if (c == '"') {
            inQuotes = !inQuotes;
            buffer += c;
        }
        else if (c == delimiter && !inQuotes) {
            list.push_back(buffer);
            buffer.clear();
        }
        else {
            buffer += c;
        }
    }
    if (!buffer.empty() || string.back() == delimiter) {
        list.push_back(buffer);
    }

    return list;
}

int gui::Client::findPlayer(int id)
{
    for (int i = 0; i < (int)_players->size(); ++i) {
        std::shared_ptr<gui::Player> entity = (*_players)[i];

        if (entity->getId() == id)
            return i;
    }
    return -1;
}

int gui::Client::findEgg(int id) {
    for (int i = 0; i < (int)_eggs->size(); ++i) {
        std::shared_ptr<gui::Egg> entity = _eggs->operator[](i);

        if (entity->getId() == id)
            return i;
    }
    return -1;
}

int gui::Client::findTile(int x, int y)
{
    for (int i = 0; i < (int)_map->size(); ++i) {
        std::shared_ptr<gui::Tile> tile = std::dynamic_pointer_cast<gui::Tile>(_map->at(i));

        if (tile->getCoord() == std::make_pair(x, y))
            return i;
    }
    return -1;
}

/************************************************************
**                  >>>>    SETTERS   <<<<                 **
************************************************************/

void gui::Client::setPlayers(std::shared_ptr<std::vector<std::shared_ptr<Player>>> players)
{
    _players = players;
}

void gui::Client::setMap(std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> map)
{
    _map = map;
}

/************************************************************
**               >>>>   GETTERS   <<<<                     **
************************************************************/

std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> gui::Client::getEggs()
{
    return _eggs;
}

std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> gui::Client::getPlayers()
{
    return _players;
}

std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> gui::Client::getMap()
{
    return _map;
}

std::shared_ptr<std::vector<std::string>> gui::Client::getTeams()
{
    if (_teams->empty()) {
        return {};
    }
    return _teams;
}
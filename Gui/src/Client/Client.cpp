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
#include <vector>


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/

gui::Client::Client() : _socket(), _serverAddr(), _list()
{
}

gui::Client::~Client()
{
}

gui::Client& gui::Client::getInstance()
{
    static Client instance;
    return instance;
}

/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void gui::Client::sendCommand(std::string command) const
{
    send(this->_socket, command.c_str(), command.size(), 0);
}

void gui::Client::catchCommand(std::shared_ptr<std::vector<gui::Player>> list)
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
    std::pair<int, int>

    list = this->splitString(string);

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

        if (list.size() == 3 && list[0] == "msz") {
            coord.first = atoi(list[1].c_str());
            coord.second = atoi(list[2].c_str());
        }

        if (coord.first && coord.second && coord.first > 0 && coord.second > 0)
            return coord;
        throw gui::WrongMapSize();
    }
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

    if (this->findPlayer(id) != -1)
        throw PlayerIdAlreadyUsed();

    if (id && x && y && orientation && level && id >= 0 &&
        x >= 0 && x < coord.first &&
        y >= 0 && y < coord.second &&
        orientation > 0 && orientation < 5 &&
        level > 0 && level < 9) {
        this->_list->emplace_back(id, position, static_cast<Orientation>(orientation), level, list[6]);
    } else {
        throw gui::WrongPlayerValue();
    }
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
        throw WrongPlayerId();

    if (id && id > 0) {
        // replace by an other model
        this->_list->erase(this->_list->begin() + findPlayer(id));
    }
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
    for (int i = 0; i < this->_list->size(); ++i) {
        const gui::Player& entity = (*this->_list)[i];

        if (entity.getId() == id)
            return i;
    }
    return -1;
}

/************************************************************
**                  >>>>    SETTERS   <<<<                 **
************************************************************/

/************************************************************
**               >>>>   GETTERS   <<<<                     **
************************************************************/

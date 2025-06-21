/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Client.hpp
*/

#ifndef ZAPPY_CLIENT_HPP
    #define ZAPPY_CLIENT_HPP

    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <iostream>
    #include "AEntity.hpp"
    #include "AItem.hpp"
    #include "Player.hpp"
    #include "Tile.hpp"
    #include "Error.hpp"
    #include <vector>
    #include <iostream>
    #include <memory>
    #include <map>

namespace gui {
    class Client {
        public:
            static Client &getInstance();

            void sendCommand(const std::string& command) const;

            void setPlayers(std::vector<std::shared_ptr<Player>> players);

            [[nodiscard]] std::pair<int, int> msz() const; // map size

        private:
            Client();
            ~Client();
            Client(const Client&) = delete;
            Client& operator=(const Client &) = delete;

            void connectToServer();
            void receiveLoop();

            void bct(std::vector<std::string> stringArray); // content of a tile
            void tna(std::vector<std::string> stringArray); // name of all the teams
            void pnw(std::vector<std::string> stringArray); // connection of a new player
            void ppo(std::vector<std::string> stringArray); // player’s position
            void plv(std::vector<std::string> stringArray); // player’s level
            void pin(std::vector<std::string> stringArray); // player’s inventory
            void pex(std::vector<std::string> stringArray); // expulsion
            void pbc(std::vector<std::string> stringArray); // broadcast
            void pic(std::vector<std::string> stringArray); // start of an incantation
            void pie(std::vector<std::string> stringArray); // end of an incantation
            void pfk(std::vector<std::string> stringArray); // egg laying by the player
            void pdr(std::vector<std::string> stringArray); // resource dropping
            void pgt(std::vector<std::string> stringArray); // resource collecting
            void pdi(std::vector<std::string> stringArray); // death of a player
            void enw(std::vector<std::string> stringArray); // an egg was laid by a player
            void ebo(std::vector<std::string> stringArray); // player connection for an egg
            void edi(std::vector<std::string> stringArray); // death of an egg
            void sgt(std::vector<std::string> stringArray); // time unit request
            void sst(std::vector<std::string> stringArray); // time unit modification
            void seg(std::vector<std::string> stringArray); // end of game
            void smg(std::vector<std::string> stringArray); // message from the server
            void suc(std::vector<std::string> stringArray); // unknown command
            void sbp(std::vector<std::string> stringArray); // command parameter

            static std::vector<std::string> splitString(const std::string &string);
            static std::shared_ptr<Model> safeModelLoader(const std::string& string);
            int findPlayer(int id);

            int _socket;
            bool _isActive;
            std::vector<std::shared_ptr<gui::Player>> _Players;
            std::vector<std::shared_ptr<gui::Tile>> _Map;
            std::vector<std::shared_ptr<Model>> _models;
            std::vector<std::string> _teams;
    };
}

inline void SendCommand(const std::string& command)
{
    gui::Client::getInstance().sendCommand(command);
}

inline std::pair<int, int> Msz()
{
    return gui::Client::getInstance().msz();
}

#endif //ZAPPY_CLIENT_HPP

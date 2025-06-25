/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Client.hpp
*/

#ifndef ZAPPY_CLIENT_HPP
    #define ZAPPY_CLIENT_HPP

    #include <map>
    #include <vector>
    #include <thread>
    #include <memory>
    #include <utility>
    #include <iostream>
    #include <iostream>
    #include <functional>
    #include <arpa/inet.h>
    #include <sys/socket.h>

    #include "Tile.hpp"
    #include "AItem.hpp"
    #include "Scene.hpp"
    #include "Error.hpp"
    #include "Player.hpp"
    #include "Display.hpp"
    #include "AEntity.hpp"

namespace gui {
    class Client {
        public:
            Client(std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> players, std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> map,
                std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> eggs, std::shared_ptr<Camera> camera, std::shared_ptr<CamState> camState,
                std::shared_ptr<std::vector<std::shared_ptr<Model>>> models, std::shared_ptr<Display> display, std::string hostname, std::string port);
            ~Client();

            void sendCommand(const std::string& command) const;

            void setPlayers(std::shared_ptr<std::vector<std::shared_ptr<Player>>> players);
            void setMap(std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> map);

            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> getEggs();
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> getPlayers();
            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> getMap();

            void drawPlayers();
        private:
            void connectToServer();
            void receiveLoop();

            void msz(std::vector<std::string> stringArray); // map size
            void bct(std::vector<std::string> stringArray); // content of a tile
            void tna(std::vector<std::string> stringArray); // name of all the teams
            void pnw(std::vector<std::string> stringArray); // connection of a new player
            void ppo(std::vector<std::string> stringArray); // player’s position
            void plv(std::vector<std::string> stringArray); // player’s level
            void pin(std::vector<std::string> stringArray); // player’s inventory
            void pex(std::vector<std::string> stringArray); // expulsion
            void pbc(std::vector<std::string> stringArray); // broadcast
            void pic(std::vector<std::string> stringArray); // start of an incantation
            void pie(std::vector<std::string> stringArray) const; // end of an incantation
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
            void suc(const std::vector<std::string>& stringArray); // unknown command
            void sbp(const std::vector<std::string>& stringArray); // command parameter

            std::vector<std::string> splitString(const std::string &string, char delimiter);
            std::shared_ptr<Model> safeModelLoader(const std::string& string);
            int findPlayer(int id);

            std::mutex _mutex;
            std::shared_ptr<Camera> _camera;
            std::shared_ptr<CamState> _camState;

            std::string _hostname;
            std::string _port;
            int _socket;
            bool _isActive;

            std::thread _thread;
            std::pair<int, int> _size;
            std::vector<std::string> _teams;
            std::shared_ptr<Display> _display;
            std::shared_ptr<std::vector<std::shared_ptr<Model>>> _models;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> _eggs;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> _map;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> _players;
    };
}


#endif //ZAPPY_CLIENT_HPP

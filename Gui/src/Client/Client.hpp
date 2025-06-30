/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Client.hpp
*/

#ifndef ZAPPY_CLIENT_HPP
    #define ZAPPY_CLIENT_HPP

    #include <thread>

    #include "Scene.hpp"
    #include "Sockets.hpp"
    #include "TeamsDisplay.hpp"

namespace gui {
    class Client {
        public:
            Client(std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> players, std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> map,
                   std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> eggs, const std::shared_ptr<Camera>& camera, const std::shared_ptr<CamState>& camState,
                   std::shared_ptr<std::vector<std::shared_ptr<Model>>> models, const std::shared_ptr<Display>& display, const std::shared_ptr<int>& timeUnit,
                   std::shared_ptr<std::string> hostname, std::shared_ptr<std::string> port);
            ~Client();

            void sendCommand(const std::string& command);

            void setMap(std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> map);
            void setPlayers(std::shared_ptr<std::vector<std::shared_ptr<Player>>> players);

            std::shared_ptr<std::vector<std::string>> getTeams();
            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> getEggs();
            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> getMap();
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> getPlayers();

            void drawPlayers();
            void newServerConnection();
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
            void suc(const std::vector<std::string>& stringArray); // unknown command
            void sbp(const std::vector<std::string>& stringArray); // command parameter

            std::vector<std::string> splitString(const std::string &string, char delimiter);
            int findPlayer(int id);
            int findEgg(int id);
            int findTile(int x, int y);

            std::shared_ptr<Camera> _camera;
            std::shared_ptr<CamState> _camState;


            std::string _previousPort;
            std::string _previousHostname;
            std::shared_ptr<std::string> _hostname;
            std::shared_ptr<std::string> _port;
            Socket _socket;

            bool _isActive;

            std::thread _thread;
            std::pair<int, int> _size;
            std::shared_ptr<int> _timeUnit;
            std::shared_ptr<Display> _display;
            std::shared_ptr<TeamsDisplay> _displayTeams;
            std::shared_ptr<std::vector<std::string>> _teams;
            std::shared_ptr<std::map<std::string, Color>> _teamColors;
            std::shared_ptr<std::vector<std::shared_ptr<Model>>> _models;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> _eggs;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> _map;
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> _players;
    };
}


#endif //ZAPPY_CLIENT_HPP

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Client.hpp
*/

#ifndef ZAPPY_CLIENT_HPP
    #define ZAPPY_CLIENT_HPP

    #include <mutex>
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

            /**
             * @brief Starts the client and connects to the server.
             * This function initializes the client, connects to the server, and starts the receive loop in a separate thread.
             */
            void newServerConnection();

            /**
             * @brief Sends a command to the server.
             * @param command The command to send to the server.
             */
            void sendCommand(const std::string& command);


            /**
             * @biref set the map, players, eggs and teams
             * @param map A shared pointer to a vector of shared pointers to Tile objects representing the map.
             */
            void setMap(std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> map);

            /**
             * @brief set the Players
             * @param players A shared pointer to a vector of shared pointers to Player objects representing the players.
             */
            void setPlayers(std::shared_ptr<std::vector<std::shared_ptr<Player>>> players);

            /**
             * @brief get the teams
             * @return A shared pointer to a vector of strings representing the teams.
             */
            std::shared_ptr<std::vector<std::string>> getTeams();

            /**
             * @brief get the eggs
             * @return A shared pointer to a vector of shared pointers to Egg objects representing the eggs
             */
            std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> getEggs();

            /**
             * @brief get the map
             * @return A shared pointer to a map of strings to Color objects representing the map.
             */
            std::shared_ptr<std::vector<std::shared_ptr<gui::Tile>>> getMap();

            /**
             * @brief get the players
             * @return A shared pointer to a vector of shared pointers to Model objects representing the players.
             */
            std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> getPlayers();

        private:
            /**
             * @brief Receives data from the server in a loop.
             * This function continuously listens for messages from the server and processes them.
             */
            void receiveLoop();

            /**
             * @brief connects to the server using the provided hostname and port.
             */
            void connectToServer();

            /**
             * @brief Command handle for map size
             * @param stringArray A vector of strings containing the command parameters.
             */
            void msz(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for tile content
             * @param stringArray A vector of strings containing the command parameters.
             */
            void bct(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for player position
             * @param stringArray A vector of strings containing the command parameters.
             */
            void ppo(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for the name of all the teams
             * @param stringArray A vector of strings containing the command parameters.
             */
            void tna(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for the connection of a new player
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pnw(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a player's level
             * @param stringArray A vector of strings containing the command parameters.
             */
            void plv(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a player's inventory
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pin(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a expulsion
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pex(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a player message / broadcast
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pbc(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a incantation start
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pic(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a player incantation end
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pie(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a egg laying by the player
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pfk(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a player dropping resources
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pdr(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a player taking resources
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pgt(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a player death
             * @param stringArray A vector of strings containing the command parameters.
             */
            void pdi(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a egg laid by the player but from map point of view
             * @param stringArray A vector of strings containing the command parameters.
             */
            void enw(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a connection of a player to an egg
             * @param stringArray A vector of strings containing the command parameters.
             */
            void ebo(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a egg death
             * @param stringArray A vector of strings containing the command parameters.
             */
            void edi(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a time unit request
             * @param stringArray A vector of strings containing the command parameters.
             */
            void sgt(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a time unit modification
             * @param stringArray A vector of strings containing the command parameters.
             */
            void sst(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a end of game
             * @param stringArray A vector of strings containing the command parameters.
             */
            void seg(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a message from the server
             * @param stringArray A vector of strings containing the command parameters.
             */
            void smg(std::vector<std::string> stringArray);

            /**
             * @brief Command handle for a unknown command
             * @param stringArray A vector of strings containing the command parameters.
             */
            void suc(const std::vector<std::string>& stringArray);

            /**
             * @brief Command handle for a bad command
             * @param stringArray A vector of strings containing the command parameters.
             */
            void sbp(const std::vector<std::string>& stringArray);
            
            /**
             * @brief Find the index of an egg in the eggs vector.
             * @param id The ID of the egg to find.
             * @return The index of the egg in the eggs vector, or -1 if not found.
             */
            int findEgg(int id);

            /**
             * @brief Find the index of a player in the players vector.
             * @param id The ID of the player to find.
             * @return The index of the player in the players vector, or -1 if not found.
             */
            int findPlayer(int id);

            /**
             * @brief Find the index of a tile in the map vector.
             * @param x The x-coordinate of the tile to find.
             * @param y The y-coordinate of the tile to find.
             * @return The index of the tile in the map vector, or -1 if not found.
             */
            int findTile(int x, int y);

            /**
             * @brief Split a string into a vector of strings based on a delimiter.
             * @param string The input string to split.
             * @param delimiter The character used to split the string.
             * @return A vector of strings resulting from the split operation.
             */
            std::vector<std::string> splitString(const std::string &string, char delimiter);

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


#endif
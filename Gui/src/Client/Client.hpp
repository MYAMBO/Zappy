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
    #include <vector>
    #include <iostream>
    #include <memory>
    #include <map>

namespace gui {
    class Client {
        public:
            static Client &getInstance();

            void connect();

            void sendCommand(std::string command) const;

            void setPlayers(std::vector<std::shared_ptr<Player>> players);
            void setItems(std::vector<std::shared_ptr<AItem>> items);

            [[nodiscard]] std::pair<int, int> msz() const; // map size

        private:
            Client();
            ~Client();
            Client(const Client&) = delete;
            Client& operator=(const Client &) = delete;


            void catchCommand();

            void interpretCommand(std::string string);

            void bct(const std::string& string); // content of a tile
            void tna(std::string string); // name of all the teams
            void pnw(const std::string &string); // connection of a new player
            void ppo(std::string string); // player’s position
            void plv(std::string string); // player’s level
            void pin(std::string string); // player’s inventory
            void pex(std::string string); // expulsion
            void pbc(std::string string); // broadcast
            void pic(std::string string); // start of an incantation
            void pie(std::string string); // end of an incantation
            void pfk(std::string string); // egg laying by the player
            void pdr(std::string string); // resource dropping
            void pgt(std::string string); // resource collecting
            void pdi(const std::string& string); // death of a player
            void enw(std::string string); // an egg was laid by a player
            void ebo(std::string string); // player connection for an egg
            void edi(std::string string); // death of an egg
            void sgt(std::string string); // time unit request
            void sst(std::string string); // time unit modification
            void seg(std::string string); // end of game
            void smg(std::string string); // message from the server
            void suc(std::string string); // unknown command
            void sbp(std::string string); // command parameter

            static std::vector<std::string> splitString(const std::string &string);
            int findPlayer(int id);


            int _socket;
            sockaddr_in _serverAddr;
            std::vector<std::shared_ptr<gui::Player>> _Players;
            std::vector<std::shared_ptr<gui::Tile>> _Map;
    };

    class WrongPlayerValue : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Player's value are wrong.";
        };
    };

    class WrongTileValue : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "There is a wrong value for creating Tile.";
        };
    };

    class WrongMapSize : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Value for Map size is invalid.";
        };
    };

    class WrongTeamName : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Value for team name is invalid.";
        };
    };

    class WrongPlayerId : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "No player with this Id.";
        };
    };

    class PlayerIdAlreadyUsed : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "This Id is already used by an other player.";
        };
    };

    class InvalidNumberOfParameter : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Command with the wrong number of argument.";
        };
    };

    class UnexpectedArgumentError : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Received an unexpected argument.";
        };
    };

    class WrongPlayerLevel : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Player's level can't have negative value";
        };
    };

    class WrongInventoryValue : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Player's inventory can't have negative value";
        };
    };

    class InvalidPlayerPosition : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Player's position out of map";
        };
    };

    class InvalidIncantationLevel : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Incantation level is invalid";
        };
    };

    class WrongResourceNumber : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Resources can't have negative value";
        };
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

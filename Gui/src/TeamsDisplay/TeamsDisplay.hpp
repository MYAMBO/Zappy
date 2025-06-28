/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** TeamDisplay.hpp
*/

#ifndef ZAPPY_TEAMSDISPLAY_HPP
    #define ZAPPY_TEAMSDISPLAY_HPP

    #include <memory>
    #include <vector>
    #include <map>
    #include <raylib.h>

    #include "Egg.hpp"
    #include "Player.hpp"

namespace gui {
    class TeamsDisplay {
    public:
        TeamsDisplay(std::shared_ptr<std::vector<std::string>> teams,
                     std::shared_ptr<std::map<std::string, Color>> teamsColor,
                     std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>>_eggs,
                     std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> players);

        ~TeamsDisplay();

        void display(std::pair<int, int> coord);

        int getStatus();
        void enableIsTile();
        void disableIsTile();

    private:
        int _isTile;
        int _fontSize;
        Rectangle _tileTeams;
        std::shared_ptr<std::vector<std::string>> _teams;
        std::shared_ptr<std::map<std::string, Color>> _teamsColor;
        std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> _eggs;
        std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> _players;


        /**
         * @brief Get all the players on a Tile or on the map.
         * @return A vector with all position in list of players on this Tile / map
         */
        std::vector<int> getPlayers(std::pair<int, int> coord);

        /**
         * @brief Get all the Eggs on a Tile or on the map.
         * @return A vector with all position in list of Eggs on this Tile / map
         */
        std::vector<int> getEgg(std::pair<int, int> coord);

        int getNbrEggs(const std::string& team, std::pair<int, int> coord);
        int getNbrPlayer(const std::string& team, std::pair<int, int> coord);
    };
}

#endif //ZAPPY_TEAMSDISPLAY_HPP

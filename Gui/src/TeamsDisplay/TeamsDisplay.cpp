/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** TeamDisplay.cpp
*/

#include "TeamsDisplay.hpp"
#include "Logger.hpp"

#include <utility>

gui::TeamsDisplay::TeamsDisplay(std::shared_ptr<std::vector<std::string>> teams,
    std::shared_ptr<std::map<std::string, Color>> teamsColor,
    std::shared_ptr<std::vector<std::shared_ptr<gui::Egg>>> eggs,
    std::shared_ptr<std::vector<std::shared_ptr<gui::Player>>> players) :
    _isTile(0), _display(true), _fontSize(30),
    _tileTeams({static_cast<float>(SCREEN_WIDTH) * 0.8f, static_cast<float>(SCREEN_WIDTH) * 0.02f, static_cast<float>(SCREEN_WIDTH) * 0.8f, static_cast<float>(SCREEN_HEIGHT) * 0.7f}),
    _teams(std::move(teams)), _teamsColor(std::move(teamsColor)), _eggs(std::move(eggs)), _players(std::move(players))
{}

gui::TeamsDisplay::~TeamsDisplay() = default;

void gui::TeamsDisplay::display(std::pair<int, int> coord)
{
    if (!_display)
        return;
    DrawRectangleRec(_tileTeams, {255, 255, 255, 50});

    if (_isTile)
        DrawText("On tile :", static_cast<int>(_tileTeams.x + 25), static_cast<int>(_tileTeams.y + 30), 50, WHITE);
    else
        DrawText("On Map :", static_cast<int>(_tileTeams.x + 25), static_cast<int>(_tileTeams.y + 30), 50, WHITE);

    for (int i = 0; i < static_cast<int>(_teams->size()); ++i) {
        std::string text;
        if (_teams->at(i).size() > 15)
            text = _teams->at(i).substr(0, 15) + "... : ";
        else
            text = _teams->at(i) + " : ";

        std::string playerText = "Players : " + std::to_string(getNbrPlayer(_teams->at(i), coord));
        std::string eggsText = "Eggs : " + std::to_string(getNbrEggs(_teams->at(i), coord));
        float textX = _tileTeams.x + 25;
        float textY = _tileTeams.y + 100 * i + 125;
        DrawText(text.c_str(), static_cast<int>(textX), static_cast<int>(textY), _fontSize, _teamsColor->operator[](_teams->at(i)));
        DrawText(playerText.c_str(), static_cast<int>(textX + 25), static_cast<int>(textY + 45), _fontSize - 12, WHITE);
        DrawText(eggsText.c_str(), static_cast<int>(textX + 25), static_cast<int>(textY + 70), _fontSize - 12, WHITE);
    }
}

std::vector<int> gui::TeamsDisplay::getPlayers(std::pair<int, int> coord)
{
    std::vector<int> list;

    for (int i = 0; i < (int) _players->size(); ++i) {
        std::shared_ptr<gui::Player> entity = _players->at(i);

        Vector3 vectorThreePosition = entity->getPosition();
        std::pair<int, int> pairPosition = {vectorThreePosition.x, vectorThreePosition.z};

        if (!_isTile || pairPosition == coord)
            list.push_back(i);
    }
    return list;
}

int gui::TeamsDisplay::getNbrPlayer(const std::string& team, std::pair<int, int> coord)
{
    int nbr = 0;
    std::vector<int> playersIndice = getPlayers(coord);

    for (auto indice:playersIndice) {
        if (_players->at(indice)->getTeam() == team)
            ++nbr;
    }
    return nbr;
}

std::vector<int> gui::TeamsDisplay::getEgg(std::pair<int, int> coord)
{
    std::vector<int> list;

    for (int i = 0; i < (int) _eggs->size(); ++i) {
        std::shared_ptr<gui::Egg> entity = _eggs->at(i);

        Vector3 vectorThreePosition = entity->getPosition();
        std::pair<int, int> pairPosition = {vectorThreePosition.x, vectorThreePosition.z};

        if ( !_isTile || pairPosition == coord)
            list.push_back(i);
    }
    return list;
}

int gui::TeamsDisplay::getNbrEggs(const std::string& team, std::pair<int, int> coord)
{
    int nbr = 0;
    std::vector<int> eggsIndice = getEgg(coord);

    for (auto indice:eggsIndice) {
        if (_eggs->at(indice)->getTeam() == team)
            ++nbr;
    }
    return nbr;
}

int gui::TeamsDisplay::getStatus()
{
    return _isTile;
}

void gui::TeamsDisplay::enableIsTile()
{
    _isTile += 1;
}

void gui::TeamsDisplay::disableIsTile()
{
    _isTile -= 1;
}

void gui::TeamsDisplay::toggleDisplay()
{
    _display = !_display;
}

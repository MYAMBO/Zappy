/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Sibur
*/

#ifndef ZAPPY_SIBUR_HPP
    #define ZAPPY_SIBUR_HPP

    #include "AItem.hpp"

namespace gui {
    class Sibur : public AItem {
        public:
            Sibur(std::pair<int, int> position, float scale, std::shared_ptr<Model> model);
            ~Sibur();

            std::string getType() override;
    };
}

#endif
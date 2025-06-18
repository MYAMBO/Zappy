/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Mendiane
*/

#ifndef ZAPPY_MENDIANE_HPP
    #define ZAPPY_MENDIANE_HPP

    #include "AItem.hpp"

namespace gui {
    class Mendiane : public AItem {
        public:
            Mendiane(std::pair<int, int> position, float scale, std::shared_ptr<Model> model);
            ~Mendiane();

            std::string getType() override;
    };
}

#endif
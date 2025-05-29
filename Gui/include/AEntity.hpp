/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AEntity.hpp
*/

#ifndef ZAPPY_AEntity_HPP
#define ZAPPY_AEntity_HPP

#include <string>
#include <memory>
#include "raylib.h"
#include "./IEntity.hpp"

namespace Gui {

    class AEntity : public IEntity {
    public:
        AEntity(std::string type, Vector3 position, float scale, CLITERAL(Color) color);
        ~AEntity();
        CLITERAL(Color) getColor() override;
        std::shared_ptr<Model> getModel() override;
        float getScale() override;
        Vector3 getPosition() override;
        void setColor(CLITERAL(Color) color) override;
        void setPosition(Vector3 position) override;
        void setScale(float scale) override;
        void setModel(std::shared_ptr<Model> model) override;

    protected:
        CLITERAL(Color) _color;
        Vector3 _position;
        float _scale;
        std::shared_ptr<Model> _model;
    };
};

#endif //ZAPPY_AEntity_HPP

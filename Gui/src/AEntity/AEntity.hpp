/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AEntity
*/

#ifndef ZAPPY_AENTITY_HPP
    #define ZAPPY_AENTITY_HPP

    #include <string>
    #include "IEntity.hpp"

namespace gui {
    class AEntity : public IEntity {
    public:
        AEntity(Vector3 position, float scale, Color color);
        ~AEntity();

        Color getColor() override;
        Model getModel() override;
        float getScale() override;
        Vector3 getPosition() override;
        std::string getType() override;

        void setColor(Color color) override;
        void setScale(float scale) override;
        void setModel(Model model) override;
        void setPosition(Vector3 position) override;

    protected:
        Color _color;
        Vector3 _position;
        float _scale;
        Model _model;
    };
};

#endif //ZAPPY_AEntity_HPP

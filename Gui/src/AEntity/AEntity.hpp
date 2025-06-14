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

        /**
         * @brief Getters for the color of the entity.
         * @return Color of the entity.
         */
        Color getColor() override;

        /**
         * @brief Getters for the model of the entity.
         * @return Model of the entity.
         */
        Model getModel() override;

        /**
         * @brief Getters for the scale of the entity.
         * @return Scale of the entity.
         */
        float getScale() override;

        /**
         * @brief Getters for the position of the entity.
         * @return Position of the entity.
         */
        Vector3 getPosition() override;

        /**
         * @brief Getters for the type of the entity.
         * @return Type of the entity as a string.
         */
        std::string getType() override;


        /**
         * @brief Setters for the color of the entity.
         * @param color Color to set for the entity.
         */
        void setColor(Color color) override;

        /**
         * @brief Setters for the model of the entity.
         * @param model Model to set for the entity.
         */
        void setScale(float scale) override;

        /**
         * @brief Setters for the position of the entity.
         * @param position Position to set for the entity.
         */
        void setModel(Model model) override;

        /**
         * @brief Setters for the position of the entity.
         * @param position Position to set for the entity.
         */
        void setPosition(Vector3 position) override;

    protected:
        Color _color;
        Vector3 _position;
        float _scale;
        Model _model;
    };
};

#endif //ZAPPY_AEntity_HPP

/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IEntity.hpp
*/

#ifndef ZAPPY_MAIN_HPP
    #define ZAPPY_MAIN_HPP

    #include <vector>
    #include <raylib.h>
    #include <memory>

namespace gui {
    class IEntity {
        public:
            virtual Color getColor() = 0;
            virtual float getScale() = 0;
            virtual Vector3 getPosition() = 0;
            virtual std::string getType() = 0;
            virtual float getRotationY() = 0;
            virtual std::shared_ptr<Model> getModel() = 0;

            virtual void setColor(Color color) = 0;
            virtual void setScale(float scale) = 0;
            virtual void setPosition(Vector3 position) = 0;
            virtual void setRotationY(float rotationY) = 0;
            virtual void setModel(std::shared_ptr<Model> model) = 0;

    };
};

#endif

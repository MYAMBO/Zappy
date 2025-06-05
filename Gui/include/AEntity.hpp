#ifndef ZAPPY_AEntity_HPP
    #define ZAPPY_AEntity_HPP

    #include <string>
    #include "IEntity.hpp"

namespace gui {
    class AEntity : public IEntity {
    public:
        AEntity(const std::string& type, Vector3 position, float scale, Color color);
        ~AEntity();

        Color getColor() override;
        Model getModel() override;
        float getScale() override;
        Vector3 getPosition() override;

        void setColor(Color color) override;
        void setPosition(Vector3 position) override;
        void setScale(float scale) override;
        void setModel(Model model) override;

    protected:
        Color _color;
        Vector3 _position;
        float _scale;
        Model _model;
    };
};

#endif //ZAPPY_AEntity_HPP

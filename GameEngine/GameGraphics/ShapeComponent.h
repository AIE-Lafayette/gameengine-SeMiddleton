#pragma once
#include "Project1/TransformComponent.h"

namespace GameGraphics
{
    enum ShapeType
    {
        CIRCLE,
        BOX
    };

    class ShapeComponent :
        public GameEngine::Component
    {
    public:
        ShapeComponent() {};
        ShapeComponent(ShapeType shapeType) : Component() { m_shapeType = shapeType; }

        void setShapeType(ShapeType shapeType) { m_shapeType = shapeType; }

        void setColor(unsigned int color) { m_color = color; }
        ShapeType getShapeType() { return m_shapeType; }

        void draw() override;

    private:
        ShapeType m_shapeType;
        unsigned int m_color = 0XFFFFFFFF;
    };
}

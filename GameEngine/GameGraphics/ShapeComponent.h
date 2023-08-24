#pragma once
#include "TransformComponent.h"

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
        ShapeComponent(ShapeType shapeType) : Component() { m_shapeType = shapeType; }

        void setColor(unsigned int color) { m_color = color; }
        ShapeType getShapeType() { return m_shapeType; }

        void draw() override;

    private:
        ShapeType m_shapeType;
        unsigned int m_color = 0XFFFFFFFF;
    };
}

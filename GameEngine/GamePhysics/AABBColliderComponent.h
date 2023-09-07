#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
    class AABBColliderComponent :
        public ColliderComponent
    {
    public:
        AABBColliderComponent(float width, float height);

        GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other);
        GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other);

        void draw() override;

        /// <summary>
        /// Gets the x value that represents the how far the box extrnds to the left
        /// </summary>
        /// <returns></returns>
        float getLeft();
        /// <summary>
        /// Gets the x value that represents the how far the box extrnds to the right
        /// </summary>
        /// <returns></returns>
        float getRight();
        /// <summary>
        /// Gets the y value that represents the how far the box extrnds to its top
        /// </summary>
        /// <returns></returns>
        float getTop();
        /// <summary>
        /// Gets the y value that represents the how far the box extrnds to its bottom
        /// </summary>
        /// <returns></returns>
        float getBottom();

    private:
        float m_width;
        float m_height;
    };

}
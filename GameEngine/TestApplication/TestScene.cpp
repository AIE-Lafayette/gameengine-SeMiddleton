#include "TestScene.h"
#include "Project1/Entity.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderComponent.h"



void TestScene::onStart()
{
	GameEngine::Entity* circle = new GameEngine::Entity();
	circle->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	GamePhysics::RigidBodyComponent* rigidBody = circle->addComponent<GamePhysics::RigidBodyComponent>();

	circle->addComponent(new GamePhysics::CircleColliderComponent(30));
	
	circle->getTransform()->setLocalPosition(100, 100);
	circle->getTransform()->setLocalPosition(25, 25);

	GameEngine::Entity* circle2 = new GameEngine::Entity();
	circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	GamePhysics::RigidBodyComponent* rigidBody2 = circle2->addComponent<GamePhysics::RigidBodyComponent>();

	circle2->addComponent(new GamePhysics::CircleColliderComponent(30));

	rigidBody2->setGravity(0);
	circle2->getTransform()->setLocalPosition(330, 700);

	circle2->getTransform()->setLocalScale(25, 25);

	rigidBody->applyForce({ 100,-100, 0 });


	circle->getTransform()->setLocalPosition(100, 100);
	circle->getTransform()->setLocalScale(25, 25);

	addEntity(circle);
	addEntity(circle2);
}
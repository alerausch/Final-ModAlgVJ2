#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Avatar.h"
#include "Ragdoll.h"
#include "Level.h"
#include <forward_list>

class LevelTwo : public Level
{
private:
	// Obstaculos estáticos
	Obstacle* _leftBlock = nullptr;
	Obstacle* _centralBlock = nullptr;
	Obstacle* _rightBlock = nullptr;
	Obstacle* _barrelBlock1 = nullptr;
	Obstacle* _barrelBlock2 = nullptr;

	// Molinos y sus joints
	Obstacle* _millBase1 = nullptr;
	Obstacle* _millBase2 = nullptr;
	Obstacle* _millBase3 = nullptr;
	Obstacle* _blade1 = nullptr;
	Obstacle* _blade2 = nullptr;
	Obstacle* _blade3 = nullptr;

	b2RevoluteJoint* revJointMill1 = nullptr;
	b2RevoluteJoint* revJointMill2 = nullptr;
	b2RevoluteJoint* revJointMill3 = nullptr;
	b2RevoluteJoint* revJointRodBob = nullptr;

	// Obstaculos dinámicos

	Obstacle* _pendulumRod = nullptr;
	Obstacle* _pendulumBob = nullptr;

	// Barril
	Barrel* _barrel = nullptr;

	bool ragdollTouchSensor;
	bool applyForce = true;
	bool isGoingDown = true;
	float previousValue = 0.0f;


public:
	LevelTwo(sf::RenderWindow* wnd, float frameTime, bool viewBodies);
	bool LevelTwo::CheckCollisions() override;
	int LevelTwo::Update(float dt, bool viewBodies) override;
	void LevelTwo::UpdatePhysics() override;
	void LevelTwo::Draw(sf::RenderWindow& RW) override;
	~LevelTwo();
};


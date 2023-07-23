#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Avatar.h"
#include "Ragdoll.h"
#include "Level.h"
#include <forward_list>

class LevelOne : public Level
{
private:
	// Obstaculos estáticos
	Obstacle* _leftBlock = nullptr;
	Obstacle* _centralBlock = nullptr;
	Obstacle* _rightBlock = nullptr;
	Obstacle* _barrelBlock1 = nullptr;
	Obstacle* _barrelBlock2 = nullptr;
	Obstacle* _testBox = nullptr;

	// Obstaculos dinámicos
	Obstacle* _leftBox = nullptr;
	Obstacle* _centralBox = nullptr;
	Obstacle* _rightBox = nullptr;
	
	Obstacle* _leftBox1 = nullptr;
	Obstacle* _centralBox1 = nullptr;
	Obstacle* _rightBox1 = nullptr;

	Obstacle* _log1 = nullptr;
	Obstacle* _log2 = nullptr;
	Obstacle* _log3 = nullptr;
	Obstacle* _log4 = nullptr;

	b2RevoluteJoint* revJointRodBob;

	Obstacle* _leftBox2 = nullptr;
	Obstacle* _rightBox2 = nullptr;

	Obstacle* _leftBox3 = nullptr;
	Obstacle* _rightBox3 = nullptr;

	Obstacle* _leftBox4 = nullptr;
	Obstacle* _centralBox4 = nullptr;
	Obstacle* _rightBox4 = nullptr;

	Obstacle* _pendulumRod = nullptr;
	Obstacle* _pendulumBob = nullptr;

	Barrel* _barrel = nullptr;

	bool ragdollTouchSensor;
	bool applyForce;
	bool isGoingDown;
	float previousValue;

public:
	LevelOne(sf::RenderWindow* wnd, float frameTime, bool viewBodies);
	bool LevelOne::CheckCollisions() override;
	int LevelOne::Update(float dt, bool viewBodies) override;
	void LevelOne::UpdatePhysics() override;
	void LevelOne::Draw(sf::RenderWindow& RW) override;
	~LevelOne();
};


#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Avatar.h"
#include "Ragdoll.h"
#include <forward_list>
#include "Obstacle.h"
#include "Barrel.h"
#include "MyContactListener.h"
/**
* @brief Clase abstracta que representa un nivel con sus características base y es donde se procesa toda la simulación de Box2D. 
* Contiene las paredes, techo, piso y la lista de ragdolls en pantalla. Los niveles heredan de esta clase e implementan sus respectivos métodos.
*/

class Level
{
protected:
	// Objetos de box2d
	b2World* phyWorld;
	SFMLRenderer* debugRender;
	std::forward_list<Ragdoll*> _ragdollList;
	bool levelComplete;
	float frameTime;
	bool viewBodies;
	float delay;
	float timer;
	b2Body* groundBody = nullptr;
	b2Body* leftWallBody = nullptr;
	b2Body* rightWallBody = nullptr;
	b2Body* roofBody = nullptr;
	MyContactListener* listener;
	

public:
	Level(sf::RenderWindow* wnd, float frameTime, bool viewBodies);
	virtual int Update(float dt, bool viewBodies) { return 0; };
	virtual void UpdatePhysics();
	virtual bool CheckCollisions() { return false; };
	void LaunchRagdoll(sf::Vector2f position, float distance, float angle);
	virtual void Draw(sf::RenderWindow& RW);
	~Level();
};


#pragma once
#include "Avatar.h"
#include <iostream>
#include "SFMLRenderer.h"
#include "Box2DHelper.h"
/**
* @brief Clase que representa el barril en escena. Compuesta por algunos bodies BOX2D, una textura y su sprite correspondiente.
*/
class Barrel
{
protected:
	// Cuerpos de Box2D
	b2Body* barrelLeftWall = nullptr;
	b2Body* barrelRightWall = nullptr;
	b2Body* barrelGroundBody = nullptr;
	b2Body* barrelMarker = nullptr;
	// Objetos SFML
	Sprite* sprBarrel;
	Texture* texturaBarrel;
public:
	bool collision;
	Barrel(Vector2f pos, b2World* phyWorld);
	void Draw(sf::RenderWindow& RW);
	void Update();
	bool CheckCollisions();
	~Barrel();
};






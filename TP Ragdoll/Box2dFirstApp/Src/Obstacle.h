#pragma once
#include <iostream>
#include "SFMLRenderer.h"
#include "Box2DHelper.h"
#include "Avatar.h"

using namespace sf;
/**
* @brief Clase que representa un obstaculo del juego. Incluye un body, un avatar y su textura correspondiente.
*/
class Obstacle
{
private:

	b2Body* _body = nullptr;
	Avatar* _bodyAvatar = nullptr;
	Texture _bodyTexture;

public:

	Obstacle(Vector2f pos, b2World* phyWorld, float width, float height, std::string path, std::string objType, float density);
	void Draw(sf::RenderWindow& RW);
	void Update();
	void ApplyForce(b2Vec2& force);
	b2Body* GetBody() { return this->_body; };
	~Obstacle();

};


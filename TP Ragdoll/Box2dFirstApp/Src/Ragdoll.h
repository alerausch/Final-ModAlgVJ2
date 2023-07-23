#pragma once
#include "Avatar.h"
#include <iostream>
#include "SFMLRenderer.h"
#include "Box2DHelper.h"

using namespace sf;
/**
* @brief Clase que representa un ragdoll. Compuesta por los bodies del cuerpo y sus respectivos avatares.
*/
class Ragdoll
{
private:
	// Cuerpos de box2d
	b2Body* cuerpoAux = nullptr;
	b2Body* headBody = nullptr;
	b2Body* torsoBody = nullptr;
	b2Body* leftLegBody = nullptr;
	b2Body* rightLegBody = nullptr;
	b2Body* rightArmBody = nullptr;
	b2Body* leftArmBody = nullptr;
	b2Body* ragSensorBody = nullptr;
	// Objetos SFML
	Avatar* headAvatar = nullptr;
	Avatar* torsoAvatar = nullptr;
	Avatar* leftLegAvatar = nullptr;
	Avatar* rightLegAvatar = nullptr;
	Avatar* leftArmAvatar = nullptr;
	Avatar* rightArmAvatar = nullptr;
	// texturas y sprites SFML
	Texture texturaFondo;
	Sprite sprFondo;
	// texturas del avatar
	Texture texturaHead;
	Texture texturaTorso;
	Texture texturaLegLeft;
	Texture texturaLegRight;
	Texture texturaArmLeft;
	Texture texturaArmRight;
	b2Draw* g_debugDraw = nullptr;

public:

	Ragdoll(Vector2f pos, b2World* phyWorld, bool applyForce, b2Vec2 forceVector, float angle);
	void Draw(sf::RenderWindow& RW);
	void Update();
	bool CheckCollisions();
	~Ragdoll();
};


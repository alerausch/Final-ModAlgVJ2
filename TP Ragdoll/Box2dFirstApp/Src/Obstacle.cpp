#include "Obstacle.h"
Obstacle::Obstacle(Vector2f pos, b2World* phyWorld, float width, float height, std::string path, std::string objType, float density)
{
	if (objType == "_static") {
		_body = Box2DHelper::CreateRectangularStaticBody(phyWorld, width, height);
		_body->GetFixtureList()->SetFriction(1.0f);
	}
	else if (objType == "_dynamic") {
		_body = Box2DHelper::CreateRectangularDynamicBody(phyWorld, width, height, density, 1.0f, 0.5f);
	}
	else if (objType == "_wheel"){
		_body = Box2DHelper::CreateCircularDynamicBody(phyWorld, width, density, 1.0f, 0.5f);
	}
	else {
		return;
	}
	_body->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);

	_bodyTexture.loadFromFile(path);
	_bodyTexture.setSmooth(true);
	_bodyAvatar = new Avatar(_body, new sf::Sprite(_bodyTexture));
}

void Obstacle::Draw(sf::RenderWindow& RW) {
	
	_bodyAvatar->Dibujar(RW);

}

void Obstacle::Update()
{
	_bodyAvatar->Actualizar();

}

void Obstacle::ApplyForce(b2Vec2& force)
{
	_body->ApplyForceToCenter(force, true);
}

Obstacle::~Obstacle() {
	delete _bodyAvatar;
}
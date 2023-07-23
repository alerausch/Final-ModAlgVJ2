#include "Barrel.h"
Barrel::Barrel(Vector2f pos, b2World* phyWorld)
{
	this->collision = false;
	
	// Definiciones de objetos Box2D

	barrelLeftWall = Box2DHelper::CreateRectangularStaticBody(phyWorld, 1.f, 9);
	barrelLeftWall->SetTransform(b2Vec2(pos.x - 3, pos.y), 0.0f);

	barrelRightWall = Box2DHelper::CreateRectangularStaticBody(phyWorld, 1.f, 9);
	barrelRightWall->SetTransform(b2Vec2(pos.x + 3, pos.y), 0.0f);

	barrelGroundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 6, 1);
	barrelGroundBody->SetTransform(b2Vec2(pos.x, pos.y + 4), 0.0f);

	barrelMarker = Box2DHelper::CreateRectangularStaticBody(phyWorld, 2, 4);
	barrelMarker->SetTransform(b2Vec2(pos.x, pos.y + 1.f), 0.0f);
	barrelMarker->GetFixtureList()->SetSensor(true);

	//Instancia de Avatar para el barril

	sprBarrel = new Sprite();
	texturaBarrel = new Texture();
	texturaBarrel->loadFromFile("../src/assets/images/barrel2.png");
	texturaBarrel->setSmooth(true);
	sprBarrel->setTexture(*texturaBarrel);
	sprBarrel->setScale(0.017f, 0.019f);
	sprBarrel->setOrigin(texturaBarrel->getSize().x / 2, texturaBarrel->getSize().y / 2);
	sprBarrel->setPosition(pos);

}

void Barrel::Draw(sf::RenderWindow& RW)
{
	RW.draw(*sprBarrel);
}

void Barrel::Update()
{

}

bool Barrel::CheckCollisions()
{
	b2ContactEdge* c;
	c = barrelMarker->GetContactList(); //obtenemos la lista de los contactos
	while (c != NULL) { //mientras c no sea nulo hay contacto
		b2Contact* contact = c->contact;
		if (contact->IsTouching() && !collision) {
			std::cout << "Sensor de barril colisionando" << std::endl;
			this->collision = true;
		}
		c = c->next;
	}
	if (this->collision)
		return true;
	else
		return false;
}

Barrel::~Barrel()
{

}
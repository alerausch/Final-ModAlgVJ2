#include "Ragdoll.h"

Ragdoll::Ragdoll(Vector2f pos, b2World* phyWorld, bool applyForce, b2Vec2 forceVector, float angle) 
{
	// Definiciones de objetos Box2D

	headBody = Box2DHelper::CreateCircularDynamicBody(phyWorld, 1.0f, 0.2f, 0.50f, 0.5f);
	headBody->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
	// body torso
	torsoBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.9f, 2.60f, 0.2f, 1.0f, 0.5f);
	torsoBody->SetTransform(b2Vec2(pos.x, pos.y + 2.2f), 0.0f);
	//body brazo izquierdo
	leftArmBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 0.7f, 2.2f, 0.2f, 0.50f, 0.5f);
	leftArmBody->SetTransform(b2Vec2(pos.x - 1.3f, pos.y + 2.4f), 0.0f);
	//body brazo derecho
	rightArmBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 0.7f, 2.2f, 0.2f, 0.50f, 0.5f);
	rightArmBody->SetTransform(b2Vec2(pos.x + 1.3f, pos.y + 2.45f), 0.0f);
	//body pierna izquierda
	leftLegBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 0.85f, 2.2f, 0.2f, 1.0f, 0.5f);
	leftLegBody->SetTransform(b2Vec2(pos.x - 0.65f, pos.y + 4.f), 0.0f);
	//body pierna derecha
	rightLegBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 0.85f, 2.2f, 0.2f, 1.0f, 0.5f);
	rightLegBody->SetTransform(b2Vec2(pos.x + 0.65f, pos.y + 4.f), 0.0f);

	ragSensorBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 0.5f, 0.5f, 0.1f, 0.1f, 0.1f);
	ragSensorBody->SetTransform(b2Vec2(pos.x, pos.y + 2.2f), 0.0f);
	ragSensorBody->GetFixtureList()->SetSensor(true);

	// Definiciones de joints del ragdoll

	//joint cabeza torso
	b2DistanceJointDef jointEsferasDef;
	jointEsferasDef.Initialize(headBody, torsoBody, b2Vec2(headBody->GetWorldCenter().x, headBody->GetWorldCenter().y + 0.3), b2Vec2(torsoBody->GetWorldCenter().x, torsoBody->GetWorldCenter().y - 0.12f));
	jointEsferasDef.length = 0.01f;
	jointEsferasDef.maxLength = 0.02f;
	jointEsferasDef.collideConnected = true;
	b2LinearStiffness(jointEsferasDef.stiffness, jointEsferasDef.damping, 1.5f, 0.2f, jointEsferasDef.bodyA, jointEsferasDef.bodyB);
	b2DistanceJoint* jointEsferas = (b2DistanceJoint*)phyWorld->CreateJoint(&jointEsferasDef);
	jointEsferas->SetDamping(0.5);
	jointEsferas->SetStiffness(15);

	//joint torso con sensor
	b2DistanceJointDef jointSensorDef;
	jointSensorDef.Initialize(torsoBody, ragSensorBody, b2Vec2(torsoBody->GetWorldCenter().x, torsoBody->GetWorldCenter().y), b2Vec2(ragSensorBody->GetWorldCenter().x, ragSensorBody->GetWorldCenter().y));
	jointSensorDef.length = 0.01f;
	jointSensorDef.maxLength = 0.05f;
	jointSensorDef.collideConnected = false;
	b2DistanceJoint* jointSensor = (b2DistanceJoint*)phyWorld->CreateJoint(&jointSensorDef);
	jointSensor->SetDamping(0.5);

	//joint torso brazo izq
	b2DistanceJointDef jointTorsoBrazoIzqDef;
	b2Vec2 anchorBrazo = b2Vec2(leftArmBody->GetPosition().x + 0.35, leftArmBody->GetPosition().y - 0.55);
	b2Vec2 anchorTorso = b2Vec2(torsoBody->GetPosition().x - 0.7, torsoBody->GetPosition().y - 0.8);
	jointTorsoBrazoIzqDef.Initialize(torsoBody, leftArmBody, anchorTorso, anchorBrazo);
	jointTorsoBrazoIzqDef.length = 0.1f;
	jointTorsoBrazoIzqDef.damping = 0.5f;
	jointTorsoBrazoIzqDef.collideConnected = true;
	b2LinearStiffness(jointTorsoBrazoIzqDef.stiffness, jointTorsoBrazoIzqDef.damping, 5.0f, 0.9f, jointTorsoBrazoIzqDef.bodyA, jointTorsoBrazoIzqDef.bodyB);
	b2DistanceJoint* jointTorsoBrazoIzq = (b2DistanceJoint*)phyWorld->CreateJoint(&jointTorsoBrazoIzqDef);
	
	// joint torso brazo der
	b2DistanceJointDef jointTorsoBrazoDerDef;
	anchorBrazo = b2Vec2(rightArmBody->GetPosition().x - 0.35, rightArmBody->GetPosition().y - 0.55);
	anchorTorso = b2Vec2(torsoBody->GetPosition().x + 0.7, torsoBody->GetPosition().y - 0.8);
	jointTorsoBrazoDerDef.Initialize(torsoBody, rightArmBody, anchorTorso, anchorBrazo);
	jointTorsoBrazoDerDef.length = 0.1f;
	jointTorsoBrazoIzqDef.damping = 0.5f;
	jointTorsoBrazoDerDef.collideConnected = true;
	b2LinearStiffness(jointTorsoBrazoDerDef.stiffness, jointTorsoBrazoDerDef.damping, 5.0f, 0.9f, jointTorsoBrazoDerDef.bodyA, jointTorsoBrazoDerDef.bodyB);
	b2DistanceJoint* jointTorsoBrazoDer = (b2DistanceJoint*)phyWorld->CreateJoint(&jointTorsoBrazoDerDef);

	//joint torso pierna izq
	b2DistanceJointDef jointTorsoPiernaIzqDef;
	b2Vec2 anchorPierna = b2Vec2(leftLegBody->GetPosition().x, leftLegBody->GetPosition().y - 0.35);
	anchorTorso = b2Vec2(torsoBody->GetPosition().x - 0.8, torsoBody->GetPosition().y + 1.5);
	jointTorsoPiernaIzqDef.Initialize(torsoBody, leftLegBody, anchorTorso, anchorPierna);
	jointTorsoPiernaIzqDef.length = 0.2f;
	jointTorsoPiernaIzqDef.damping = 0.5f;
	jointEsferasDef.maxLength = 0.2f;
	jointTorsoPiernaIzqDef.collideConnected = true;
	b2LinearStiffness(jointTorsoPiernaIzqDef.stiffness, jointTorsoPiernaIzqDef.damping, 5.0f, 0.9f, jointTorsoPiernaIzqDef.bodyA, jointTorsoPiernaIzqDef.bodyB);
	b2DistanceJoint* jointTorsoPiernaIzq = (b2DistanceJoint*)phyWorld->CreateJoint(&jointTorsoPiernaIzqDef);
	
	// joint torso pierna derecha
	b2DistanceJointDef jointTorsoPiernaDerDef;
	anchorPierna = b2Vec2(rightLegBody->GetPosition().x, rightLegBody->GetPosition().y - 0.35);
	anchorTorso = b2Vec2(torsoBody->GetPosition().x + 0.8, torsoBody->GetPosition().y + 1.5);
	jointTorsoPiernaDerDef.Initialize(torsoBody, rightLegBody, anchorTorso, anchorPierna);
	jointTorsoPiernaDerDef.length = 0.2f;
	jointTorsoPiernaDerDef.damping = 0.5f;
	jointEsferasDef.maxLength = 0.2f;
	jointTorsoPiernaDerDef.collideConnected = true;
	b2LinearStiffness(jointTorsoPiernaDerDef.stiffness, jointTorsoPiernaDerDef.damping, 5.0f, 0.9f, jointTorsoPiernaDerDef.bodyA, jointTorsoPiernaDerDef.bodyB);
	b2DistanceJoint* jointTorsoPiernaDer = (b2DistanceJoint*)phyWorld->CreateJoint(&jointTorsoPiernaDerDef);
	
	//Instancias de Avatar para las partes del personaje

	texturaHead.loadFromFile("../src/assets/images/head.png");
	headAvatar = new Avatar(headBody, new sf::Sprite(texturaHead));

	texturaTorso.loadFromFile("../src/assets/images/torso.png");
	torsoAvatar = new Avatar(torsoBody, new sf::Sprite(texturaTorso));

	texturaArmLeft.loadFromFile("../src/assets/images/armLeft.png");
	leftArmAvatar = new Avatar(leftArmBody, new sf::Sprite(texturaArmLeft));

	texturaArmRight.loadFromFile("../src/assets/images/armRight.png");
	rightArmAvatar = new Avatar(rightArmBody, new sf::Sprite(texturaArmRight));

	texturaLegLeft.loadFromFile("../src/assets/images/legLeft.png");
	leftLegAvatar = new Avatar(leftLegBody, new sf::Sprite(texturaLegLeft));

	texturaLegRight.loadFromFile("../src/assets/images/legRight.png");
	rightLegAvatar = new Avatar(rightLegBody, new sf::Sprite(texturaLegRight));

	// Aplicar fuerza al ragdoll
	if (applyForce)
		torsoBody->ApplyLinearImpulse(forceVector, torsoBody->GetWorldCenter(), true); // Aplicar el impulso al cuerpo en el centro de masa

}

void Ragdoll::Draw(sf::RenderWindow& RW){
	headAvatar->Dibujar(RW);
	torsoAvatar->Dibujar(RW);
	leftArmAvatar->Dibujar(RW);
	rightArmAvatar->Dibujar(RW);
	leftLegAvatar->Dibujar(RW);
	rightLegAvatar->Dibujar(RW);
}
void Ragdoll::Update()
{
	headAvatar->Actualizar();
	torsoAvatar->Actualizar();
	leftArmAvatar->Actualizar();
	rightArmAvatar->Actualizar();
	leftLegAvatar->Actualizar();
	rightLegAvatar->Actualizar();
}
bool Ragdoll::CheckCollisions()
{
	// Verificar si el ragdoll está colisionando.
	b2ContactEdge* c;
	c = ragSensorBody->GetContactList(); //obtenemos la lista de los contactos
	while (c != NULL) { //mientras c no sea nulo hay contacto
		b2Contact* contact = c->contact;
		if (contact->IsTouching()) {
			std::cout << "Ragdoll colisionando" << std::endl;
			return true;
		}
		c = c->next;
	}
	return false;
}
Ragdoll::~Ragdoll() {

	// Objetos SFML
	delete headAvatar;
	delete torsoAvatar;
	delete leftLegAvatar;
	delete rightLegAvatar;
	delete leftArmAvatar;
	delete rightArmAvatar;
}
#include "LevelTwo.h"

LevelTwo::LevelTwo(sf::RenderWindow* wnd, float frameTime, bool viewBodies) : Level(wnd, frameTime, viewBodies)
{
	std::cout << "LEVEL TWO CREADO" << std::endl;
	// Objetos estáticos
	_leftBlock = new Obstacle(sf::Vector2f(30, 92), this->phyWorld, 10, 10, "../src/assets/images/stones1.png", "_static", 0.f);
	_centralBlock = new Obstacle(sf::Vector2f(50, 92), this->phyWorld, 10, 10, "../src/assets/images/stones1.png", "_static", 0.f);
	_rightBlock = new Obstacle(sf::Vector2f(70, 92), this->phyWorld, 10, 10, "../src/assets/images/stones1.png", "_static", 0.f);
	_barrelBlock1 = new Obstacle(sf::Vector2f(87, 92), this->phyWorld, 10, 10, "../src/assets/images/stones2.png", "_static", 0.f);
	_barrelBlock2 = new Obstacle(sf::Vector2f(87, 82), this->phyWorld, 10, 10, "../src/assets/images/stones2.png", "_static", 0.f);
	
	// barril
	_barrel = new Barrel(Vector2f(87, 72.5), phyWorld);

	// Molinos y sus joints

	_millBase1 = new Obstacle(sf::Vector2f(30, 72), this->phyWorld, 2, 30, "../src/assets/images/wood.png", "_static", 0.0f);
	_millBase2 = new Obstacle(sf::Vector2f(50, 72), this->phyWorld, 2, 30, "../src/assets/images/wood.png", "_static", 0.0f);
	_millBase3 = new Obstacle(sf::Vector2f(70, 72), this->phyWorld, 2, 30, "../src/assets/images/wood.png", "_static", 0.0f);
	_blade1 = new Obstacle(sf::Vector2f(30, 57), this->phyWorld, 18, 4, "../src/assets/images/blade.png", "_dynamic", 0.1f);
	_blade2 = new Obstacle(sf::Vector2f(50, 57), this->phyWorld, 18, 4, "../src/assets/images/blade.png", "_dynamic", 0.1f);
	_blade3 = new Obstacle(sf::Vector2f(70, 57), this->phyWorld, 18, 4, "../src/assets/images/blade.png", "_dynamic", 0.1f);
	
	// Revolute Joint Molino 1
	b2RevoluteJointDef revJointMill1Def;
	revJointMill1Def.bodyA = _millBase1->GetBody();
	revJointMill1Def.bodyB = _blade1->GetBody();
	revJointMill1Def.localAnchorA.Set(0.f, -15.f); // Punto de anclaje en el centro de la base
	revJointMill1Def.localAnchorB.Set(0.f, 0.f); // Punto de anclaje en el aspa
	revJointMill1Def.enableMotor = true; // Habilitar el motor
	revJointMill1Def.motorSpeed = 4.0f; // Velocidad del motor en radianes por segundo
	revJointMill1Def.maxMotorTorque = 100;

	revJointMill1 = (b2RevoluteJoint*)phyWorld->CreateJoint(&revJointMill1Def);

	// Revolute Joint Molino 2
	b2RevoluteJointDef revJointMill2Def;
	revJointMill2Def.bodyA = _millBase2->GetBody();
	revJointMill2Def.bodyB = _blade2->GetBody();
	revJointMill2Def.localAnchorA.Set(0.f, -15.f); // Punto de anclaje en el centro de la base
	revJointMill2Def.localAnchorB.Set(0.f, 0.f); // Punto de anclaje en el aspa
	revJointMill2Def.enableMotor = true; // Habilitar el motor
	revJointMill2Def.motorSpeed = 4.0f; // Velocidad del motor en radianes por segundo
	revJointMill2Def.maxMotorTorque = 150;

	revJointMill2 = (b2RevoluteJoint*)phyWorld->CreateJoint(&revJointMill2Def);

	// Revolute Joint Molino 3
	b2RevoluteJointDef revJointMill3Def;
	revJointMill3Def.bodyA = _millBase3->GetBody();
	revJointMill3Def.bodyB = _blade3->GetBody();
	revJointMill3Def.localAnchorA.Set(0.f, -15.f); // Punto de anclaje en el centro de la base
	revJointMill3Def.localAnchorB.Set(0.f, 0.f); // Punto de anclaje en el aspa
	revJointMill3Def.enableMotor = true; // Habilitar el motor
	revJointMill3Def.motorSpeed = 4.0f; // Velocidad del motor en radianes por segundo
	revJointMill3Def.maxMotorTorque = 80;

	revJointMill3 = (b2RevoluteJoint*)phyWorld->CreateJoint(&revJointMill3Def);

	// Péndulo
	_pendulumRod = new Obstacle(sf::Vector2f(50, 20), this->phyWorld, 1, 30, "../src/assets/images/wood.png", "_dynamic", 0.07f);
	_pendulumBob = new Obstacle(sf::Vector2f(50, 35), this->phyWorld, 5, 5, "../src/assets/images/rueda.png", "_wheel", 0.15f);
	// Joint techo / vara del pendulo
	b2DistanceJointDef jointRoofRodDef;
	//jointRoofRodDef.Initialize(this->roofBody, _pendulumRod->GetBody(), b2Vec2(this->roofBody->GetWorldCenter().x, this->roofBody->GetWorldCenter().y + 3.0f), b2Vec2(_pendulumRod->GetBody()->GetWorldCenter().x, _pendulumRod->GetBody()->GetWorldCenter().y - 9));
	jointRoofRodDef.Initialize(this->roofBody, _pendulumRod->GetBody(), b2Vec2(this->roofBody->GetWorldCenter().x, this->roofBody->GetWorldCenter().y + 2.0f), b2Vec2(_pendulumRod->GetBody()->GetWorldCenter().x, _pendulumRod->GetBody()->GetWorldCenter().y - 14.5f));
	jointRoofRodDef.length = 0.1f;
	jointRoofRodDef.maxLength = 0.1f;
	jointRoofRodDef.collideConnected = true;
	b2LinearStiffness(jointRoofRodDef.stiffness, jointRoofRodDef.damping, 1.5f, 0.2f, jointRoofRodDef.bodyA, jointRoofRodDef.bodyB);
	b2DistanceJoint* jointRoofRod = (b2DistanceJoint*)phyWorld->CreateJoint(&jointRoofRodDef);
	jointRoofRod->SetDamping(0.5);
	jointRoofRod->SetStiffness(15);

	//// Joint vara del pendulo / rueda del pendulo
	
	b2RevoluteJointDef revJointRodBobDef;
	revJointRodBobDef.bodyA = _pendulumRod->GetBody();
	revJointRodBobDef.bodyB = _pendulumBob->GetBody();
	revJointRodBobDef.localAnchorA.Set(0.f, 15.f); // Punto de anclaje en el centro de la base
	revJointRodBobDef.localAnchorB.Set(0.f, 0.f); // Punto de anclaje en el aspa
	revJointRodBobDef.enableMotor = true; // Habilitar el motor
	revJointRodBobDef.motorSpeed = 4.0f; // Velocidad del motor en radianes por segundo
	revJointRodBobDef.maxMotorTorque = 80;

	revJointRodBob = (b2RevoluteJoint*)phyWorld->CreateJoint(&revJointRodBobDef);

	applyForce = true;
	isGoingDown = true;
	ragdollTouchSensor = false;
	previousValue = 0.0f;
}

void LevelTwo::Draw(sf::RenderWindow& RW)
{
	// Llamada a método de la clase padre que dibuja lista de ragdolls
	Level::Draw(RW);
	// Dibujo objetos del nivel actual
	_leftBlock->Draw(RW);
	_centralBlock->Draw(RW);
	_rightBlock->Draw(RW);
	_barrelBlock1->Draw(RW);
	_barrelBlock2->Draw(RW);

	_millBase1->Draw(RW);
	_millBase2->Draw(RW);
	_millBase3->Draw(RW);
	
	_blade1->Draw(RW);
	_blade2->Draw(RW);
	_blade3->Draw(RW);
	
	_pendulumRod->Draw(RW);
	_pendulumBob->Draw(RW);
	_barrel->Draw(RW);
}

void LevelTwo::UpdatePhysics()
{
	// Llamada al método de la clase padre que actualiza los objetos físicos
	Level::UpdatePhysics();

	// Actualizar los objetos dinámicos del nivel actual
	
	_millBase1->Update();
	_millBase2->Update();
	_millBase3->Update();
	
	_blade1->Update();
	_blade2->Update();
	_blade3->Update();
	
	_pendulumRod->Update();
	_pendulumBob->Update();

	// Actualizar la velocidad de motores
	revJointMill1->SetMotorSpeed(4.0f);
	revJointMill2->SetMotorSpeed(4.0f);
	revJointMill3->SetMotorSpeed(4.0f);
	revJointRodBob->SetMotorSpeed(2.5f);

	// Aplicar fuerza al pendulo para que incremente su velocidad progresivamente.
	previousValue = _pendulumRod->GetBody()->GetPosition().x;
	bool applyForce = _pendulumBob->GetBody()->GetPosition().x >= 50 && _pendulumBob->GetBody()->GetPosition().x <= 58 && isGoingDown;
	if (applyForce) {
		_pendulumBob->ApplyForce(b2Vec2(60.0f, 0));
	}
	if (previousValue > 54) {
		isGoingDown = false;
	}
	else if (previousValue < 44 || abs(_pendulumBob->GetBody()->GetLinearVelocity().x) < 15 && previousValue < 50) {
		isGoingDown = true;
	}

}

bool LevelTwo::CheckCollisions()
{
	// Verificar estado del sensor del barril
	if (_barrel->CheckCollisions() && !levelComplete) {
		// Si el sensor del barril es colisionado se verifica que el objeto sea un ragdoll y no cualquier otro objeto físico.
		if (!_ragdollList.empty()) {
			for (Ragdoll* ragdoll : _ragdollList) {
				if (ragdoll->CheckCollisions()) {
					//std::cout << "Level Complete" << std::endl;
					ragdollTouchSensor = true;
				}
			}
		}
	}
	if (levelComplete)
		return true;
	else
		return false;
}

int LevelTwo::Update(float dt, bool viewBodies)
{
	this->viewBodies = viewBodies;
	// Si el sensor del barril fue colisionado y el objeto es un ragdol
	bool win = _barrel->collision && ragdollTouchSensor;
	bool lose = _barrel->collision && !ragdollTouchSensor;
	if (win) {
		levelComplete = true;
		return 1; // Nivel superado y se devuelve 1 
	}
	else if (lose) {
		// Si el sensor fue colisionado por un objeto que no es un ragdoll
		return 2; // Nivel no superado y se devuelve 0
	}
	return 0;
}

LevelTwo::~LevelTwo()
{
	delete _leftBlock;
	delete _centralBlock;
	delete _rightBlock;
	delete _barrelBlock1;
	delete _barrelBlock2;
	
	delete _millBase1;
	delete _millBase2;
	delete _millBase3;
	delete _blade1;
	delete _blade2;
	delete _blade3;

	delete revJointMill1;
	delete revJointMill2;
	delete revJointMill3;
	delete revJointRodBob;

	delete _pendulumRod;
	delete _pendulumBob;
	
	delete _barrel;
}
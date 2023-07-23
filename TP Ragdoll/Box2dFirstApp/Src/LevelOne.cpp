#include "LevelOne.h"

LevelOne::LevelOne(sf::RenderWindow* wnd, float frameTime, bool viewBodies) : Level(wnd, frameTime, viewBodies)
{
	std::cout << "LEVEL ONE CREADO" << std::endl;
	// Objetos estáticos
	_leftBlock = new Obstacle(sf::Vector2f(30, 92), this->phyWorld, 10, 10, "../src/assets/images/stones1.png", "_static", 0.f);
	_centralBlock = new Obstacle(sf::Vector2f(50, 92), this->phyWorld, 10, 10, "../src/assets/images/stones1.png", "_static", 0.f);
	_rightBlock = new Obstacle(sf::Vector2f(70, 92), this->phyWorld, 10, 10, "../src/assets/images/stones1.png", "_static", 0.f);
	_barrelBlock1 = new Obstacle(sf::Vector2f(87, 92), this->phyWorld, 10, 10, "../src/assets/images/stones2.png", "_static", 0.f);
	_barrelBlock2 = new Obstacle(sf::Vector2f(87, 82), this->phyWorld, 10, 10, "../src/assets/images/stones2.png", "_static", 0.f);
	// barril
	_barrel = new Barrel(Vector2f(87, 72.5), phyWorld);

	// Objetos dinámicos
	
	// Primera linea de cajas
	_leftBox = new Obstacle(sf::Vector2f(30, 85), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	_centralBox = new Obstacle(sf::Vector2f(50, 85), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	_rightBox = new Obstacle(sf::Vector2f(70, 85), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	// Segunda linea de cajas
	_leftBox1 = new Obstacle(sf::Vector2f(30, 80), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	_centralBox1 = new Obstacle(sf::Vector2f(50, 80), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	_rightBox1 = new Obstacle(sf::Vector2f(70, 80), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	// Maderas horizontales inferior
	_log1 = new Obstacle(sf::Vector2f(39, 76.25), this->phyWorld, 20, 2.5f, "../src/assets/images/wood.png", "_dynamic", 0.12f);
	_log2 = new Obstacle(sf::Vector2f(61, 76.25), this->phyWorld, 20, 2.5f, "../src/assets/images/wood.png", "_dynamic", 0.12f);
	// Tercera linea de cajas
	_leftBox2 = new Obstacle(sf::Vector2f(40, 72.5), this->phyWorld, 5, 5, "../src/assets/images/caja1.png", "_dynamic", 0.07f);
	_rightBox2 = new Obstacle(sf::Vector2f(60, 72.5), this->phyWorld, 5, 5, "../src/assets/images/caja1.png", "_dynamic", 0.07f);
	// Cuarta linea de cajas
	_leftBox3 = new Obstacle(sf::Vector2f(40, 67.5), this->phyWorld, 5, 5, "../src/assets/images/caja1.png", "_dynamic", 0.07f);
	_rightBox3 = new Obstacle(sf::Vector2f(60, 67.5), this->phyWorld, 5, 5, "../src/assets/images/caja1.png", "_dynamic", 0.07f);
	// Madera horizontal superior
	_log3 = new Obstacle(sf::Vector2f(40, 65), this->phyWorld, 15, 2.5, "../src/assets/images/wood.png", "_dynamic", 0.12f);
	_log4 = new Obstacle(sf::Vector2f(60, 65), this->phyWorld, 15, 2.5, "../src/assets/images/wood.png", "_dynamic", 0.12f);
	// Quinta linea de cajas
	_leftBox4 = new Obstacle(sf::Vector2f(36, 60.25), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	_centralBox4 = new Obstacle(sf::Vector2f(50, 60.25), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
	_rightBox4 = new Obstacle(sf::Vector2f(64, 60.25), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);

	// Péndulo
	//_pendulumRod = new Obstacle(sf::Vector2f(50, 15), this->phyWorld, 1, 20, "../src/assets/images/wood.png", "_dynamic", 0.07f);
	//_pendulumBob = new Obstacle(sf::Vector2f(50, 25), this->phyWorld, 5, 5, "../src/assets/images/rueda.png", "_wheel", 0.15f);
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
	revJointRodBobDef.motorSpeed = 2.5f; // Velocidad del motor en radianes por segundo
	revJointRodBobDef.maxMotorTorque = 80;

	revJointRodBob = (b2RevoluteJoint*)phyWorld->CreateJoint(&revJointRodBobDef);

	applyForce = true;
	isGoingDown = true;
	ragdollTouchSensor = false;
	previousValue = 0.0f;

	//_testBox = new Obstacle(sf::Vector2f(87, 20), this->phyWorld, 5, 5, "../src/assets/images/caja.png", "_dynamic", 0.07f);
}

void LevelOne::Draw(sf::RenderWindow& RW)
{ 
	// Llamada a método de la clase padre que dibuja lista de ragdolls
	Level::Draw(RW);
	// Dibujar objetos del nivel actual
	_leftBlock->Draw(RW);
	_centralBlock->Draw(RW);
	_rightBlock->Draw(RW);
	_barrelBlock1->Draw(RW);
	_barrelBlock2->Draw(RW);
	_leftBox->Draw(RW);
	_centralBox->Draw(RW);
	_rightBox->Draw(RW);
	_leftBox1->Draw(RW);
	_centralBox1->Draw(RW);
	_rightBox1->Draw(RW);
	_log1->Draw(RW);
	_log2->Draw(RW);
	_leftBox2->Draw(RW);
	_rightBox2->Draw(RW);
	_leftBox3->Draw(RW);
	_rightBox3->Draw(RW);
	_log3->Draw(RW);
	_log4->Draw(RW);
	_leftBox4->Draw(RW);
	_centralBox4->Draw(RW);
	_rightBox4->Draw(RW);
	_pendulumRod->Draw(RW);
	_pendulumBob->Draw(RW);
	_barrel->Draw(RW);
	//_testBox->Draw(RW);
}

void LevelOne::UpdatePhysics()
{
	// Llamada al método de la clase padre que actualiza los objetos físicos
	Level::UpdatePhysics();
	
	// Actualizar los objetos dinámicos del nivel actual
	_leftBox->Update();
	_centralBox->Update();
	_rightBox->Update();
	_leftBox1->Update();
	_centralBox1->Update();
	_rightBox1->Update();
	_log1->Update();
	_log2->Update();
	_leftBox2->Update();
	_rightBox2->Update();
	_leftBox3->Update();
	_rightBox3->Update();
	_log3->Update();
	_log4->Update();
	_leftBox4->Update();
	_centralBox4->Update();
	_rightBox4->Update();
	_pendulumRod->Update();
	_pendulumBob->Update();

	//_testBox->Update();
	
	// Actualizar la velocidad del motor
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

bool LevelOne::CheckCollisions()  
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

int LevelOne::Update(float dt, bool viewBodies)
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

LevelOne::~LevelOne() 
{
	delete _leftBlock;
	delete _centralBlock;
	delete _rightBlock;
	delete _barrelBlock1;
	delete _barrelBlock2;
	delete _leftBox;
	delete _centralBox;
	delete _rightBox;
	delete _leftBox1 ;
	delete _centralBox1;
	delete _rightBox1;
	delete _log1;
	delete _log2;
	delete _log3;
	delete _log4;
	delete _leftBox2;
	delete _rightBox2;
	delete _leftBox3;
	delete _rightBox3;
	delete _leftBox4;
	delete _centralBox4;
	delete _rightBox4;
	delete _pendulumRod;
	delete _pendulumBob;
	delete revJointRodBob;
	delete _barrel;
	delete _testBox;
}
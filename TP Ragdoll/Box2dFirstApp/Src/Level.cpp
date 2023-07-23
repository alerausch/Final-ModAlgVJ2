#include "Level.h"

Level::Level(sf::RenderWindow* wnd, float frameTime, bool viewBodies) 
{
	this->viewBodies = viewBodies;
	this->frameTime = frameTime;
	levelComplete = false;
	delay = 3.0f;
	timer = 0.f;

	// Inicializar el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	listener = new MyContactListener();
	phyWorld->SetContactListener(listener);
	
	// Crear el renderer de debug y setear las banderas para que dibuje todo
	debugRender = new SFMLRenderer(wnd);

	//debugRender->SetFlags(UINT_MAX);
	//debugRender->SetFlags(b2Draw::e_shapeBit);

	phyWorld->SetDebugDraw(debugRender);

	// Piso, techo y paredes del nivel
	groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 5);
	groundBody->GetFixtureList()->SetFriction(1.0f);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 2, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 2, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	roofBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 5);
	roofBody->SetTransform(b2Vec2(50.0f, 2.0f), 0.0f);
	
}

void Level::Draw(sf::RenderWindow& RW) 
{
	// Recorrer la lista y dibujar sus elementos
	for (Ragdoll* ragdoll : _ragdollList) {
		ragdoll->Draw(RW);
	}
}

void Level::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
	if (this->viewBodies) {
		//debugRender->SetFlags(0x0001);
		debugRender->SetFlags(0x1111);
	}
	else {
		debugRender->SetFlags(0);
	}
	// actualizo las partes de los ragdolls
	if (!_ragdollList.empty()) {
		for (Ragdoll* ragdoll : _ragdollList) {
			ragdoll->Update();
		}
	}
}

void Level::LaunchRagdoll(sf::Vector2f position, float distance, float angle) {

	float angleRad = angle * b2_pi / 180;
	if (angleRad > 0){
		angleRad = -1.56;
	}

	// magnitud del impulso
	float impulse_magnitude = 2.0f; 

	// Creo un vector de impulso
	b2Vec2 impulse(impulse_magnitude * distance * std::cosf(angleRad), impulse_magnitude * distance * std::sinf(angleRad)); 
	Ragdoll* ragdoll;
	ragdoll = new Ragdoll(position, phyWorld, true, impulse, angleRad);
	_ragdollList.push_front(ragdoll);

}

Level::~Level() 
{	
	delete phyWorld;
	delete debugRender;

	for (Ragdoll* ragdoll : _ragdollList) {
		delete ragdoll;
	}

}
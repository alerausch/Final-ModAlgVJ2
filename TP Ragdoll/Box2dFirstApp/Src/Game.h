#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "SFMLRenderer.h"
#include "Avatar.h"
#include "Ragdoll.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "Menu.h"
#include "AnimatedObject.h"
#include <forward_list>

using namespace sf;

class Game
{
private:
	// Propiedades de la ventana
	RenderWindow *wnd;
	Color clearColor;
	Clock clock;

	float msgDelay; //tiempo de duración de mensajes en pantalla
	float msgTimer; //contador de tiempo de mensajes 
	bool msgEnded; //cuando el mensaje sale de pantalla es TRUE
	bool msgOnScreen; //si el mensaje esta en pantalla es TRUE
	
	bool delayStart; //delay timer comienza
	bool delayEnded; //delay timer finaliza
	float delay;//tiempo de espera antes de mostrar mensajes en pantalla
	float timer;//contador de tiempo pre-mensajes 
	
	float frecuencyHz;
	float dampingRatio;
	float frameTime; //tiempo de frame
	int fps;
	int msgId; // ID de mensaje en pantalla
	float angle; //en grados
	float angleRad; //en rad
	float dt;
	float mouseDistance;
	bool paused;
	bool playing;
	bool verCuerpos;
	int _ragdollsCount; 
	int levelCount;
	bool levelComplete;
	bool gameOver;
	Text _txtAngle;
	Text _txtRagdollsCount;
	Font _txtFont;
	Menu* _menu;
	Vector2f mousePos;
	Vector2f cannonPos;
	Texture* _pTexExplosion;
	Sprite* _pSprEnergia;
	Texture* _pTexEnergia;
	AnimatedObject* _explosion;
	std::forward_list<Ragdoll*> _ragdollList;
	Level* actualLevel = nullptr; // Variable de la clase abstracta Level en la que se almacena cualquier level en juego (se pone en práctica el polimorfismo)
	enum ObjType { _static, _dynamic };

	// Texturas y sprites SFML
	Texture texturaMouse;
	Sprite sprMouse;
	Texture texturaFondo;
	Sprite sprFondo;
	Texture texturaBase;
	Sprite sprBase;
	Texture texturaCanion;
	Sprite sprCanion;
	Texture texturaBarrel;
	Sprite sprBarrel;
	// Texturas y sprites mensajes en pantalla
	Texture texturaPaused;
	Sprite sprPaused;
	Texture texturaLevelOne;
	Sprite sprLevelOne;
	Texture texturaLevelTwo;
	Sprite sprLevelTwo;
	Texture texturaLevelComplete;
	Sprite sprLevelComplete;
	Texture texturaGameOver;
	Sprite sprGameOver;
	// Texturas del avatar del ragdoll
	Texture texturaHead;
	Texture texturaTorso;
	Texture texturaLegLeft;
	Texture texturaLegRight;
	Texture texturaArmLeft;
	Texture texturaArmRight;
	// Sonidos
	
	Sound* _menuEnterSound;
	Sound* _explosionSound;
	Sound* _gameOverSound;
	Sound* _levelCompleteSound;
	Sound* _exitSound;
	Sound* _navMenuSound;
	Music _backgroundMusic;
	Music _backgroundMenuMusic;
	SoundBuffer _menuEnterBuffer, _explosionBuffer, _gameOverBuffer, _levelCompleteBuffer, _exitBuffer, _navMenuBuffer;

public:

	// Constructores, destructores e inicializadores
	Game(int ancho, int alto,std::string titulo);
	void CheckCollisions();
	void CreateEnemy(int x, int y) {};
	void LoadLevel();
	void GameOver();
	void InitPhysics();
	void ShowMessage(int messageId);
	~Game(void);

	// Main game loop
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void Update(float dt);
	void DoEvents();
	void SetZoom();
	void ResetZoom();
};


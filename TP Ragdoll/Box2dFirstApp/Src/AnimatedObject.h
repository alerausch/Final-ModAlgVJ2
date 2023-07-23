#pragma once
#include <SFML\Graphics.hpp>
#include "PhisicObject.h"
#include <string>
#include <iostream>
#include "Animation.h"

using namespace std;
using namespace sf;

/**
* @brief Clase que contiene una animación y que le agrega control de posición, reproducción y detención de la misma, si se ejecuta en loop o no, cantidad de fps de la misma, etc.
*/

class AnimatedObject
{
public:
	AnimatedObject(string spritePath, float fps, int posX, int posY,
				bool loop, int frameW, int frameH, int framesX, int framesY);
	AnimatedObject(Texture* texture, float fps, int posX, int posY,
				bool loop, int frameW, int frameH, int framesX, int framesY);
	~AnimatedObject();
	void Update(float dt);
	void Run() { _isPlaying = true; }
	void Stop() { _isPlaying = false; _pSprAnimObj->Reset(); }
	void RunXY(int X, int Y);
	bool GetStatus() { return _isPlaying; }
	void Draw(RenderWindow* pWnd);
	Animation* _pSprAnimObj;
private:
	Texture* _pTexAnimObj;
	bool _isPlaying;
	float _acumTime;
	float _timeLapse;
	float _fps;
	bool _loop;
};


#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

/**
* @brief Clase que se encarga de ejecutar las animaciones, hereda de Sprite y por ende incorpora todos sus métodos y propiedades
*/
class Animation : public sf::Sprite
{
public:
	Animation(Texture* texture, int frameWidth, 
		int frameHeight, int framesX, int framesY);
	~Animation() {};
	void SelectFrame();
	void Reset();
	bool Animate(float acumTime, float timeLapse);
private:
	int _fps;
	int _frameW;
	int _frameH;
	int _cantFramesX;
	int _cantFramesY;
	bool _loop;
	bool _isPlaying;
	Vector2i _actualFrame;
	Texture* _pTexture;
};


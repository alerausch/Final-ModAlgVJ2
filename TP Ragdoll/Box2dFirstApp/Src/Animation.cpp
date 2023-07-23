#include "Animation.h"
#include <iostream>

Animation::Animation(Texture* texture, int frameWidth,
	int frameHeight, int framesX, int framesY)
{
	_isPlaying = false;
	_frameW = frameWidth;
	_frameH = frameHeight;
	_cantFramesX = framesX;
	_cantFramesY = framesY;
	_pTexture = texture;
	_pTexture->setSmooth(true);
	this->setTexture(*_pTexture);
	_actualFrame.x = 0;
	_actualFrame.y = 0;
	this->setScale(0.12f, 0.15f);
	this->SelectFrame();
}

void Animation::SelectFrame() 
{
	IntRect rectangleFrame(_actualFrame.x * _frameW, _actualFrame.y * _frameH, _frameW, _frameH);
	this->setTextureRect(rectangleFrame);
}

void Animation::Reset()
{
	_isPlaying = false;
	_actualFrame.x = 0;
	_actualFrame.y = 0;
	this->SelectFrame();
}

bool Animation::Animate(float acumTime, float timeLapse)
{
	SelectFrame();
	if (_actualFrame.x != _cantFramesX)
	{
		//std::cout << "Dibujando frame: " << _actualFrame.x + 1 << std::endl;
		_actualFrame.x += 1;
	}
	else {
		_actualFrame.x = 0;
		SelectFrame();
		return false;
	}
	return true;
}
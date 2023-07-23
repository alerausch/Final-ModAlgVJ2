#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class PhisicObject
{
public:
	PhisicObject(){};
	PhisicObject(string filename);
	~PhisicObject();

	void Draw(RenderWindow* pWnd);
	virtual int Update(float dt) { return 0; }

	void SetScale(float uniformScale) { _pSpr->setScale(uniformScale, uniformScale); }

	void SetPosition(Vector2f pos) { _position = pos; }
	void SetAcceleration(Vector2f acc) { _acceleration = acc; }
	void SetVelocity(Vector2f vel) { _velocity = vel; }
	void SetRotation(float rot) { _rotation = rot; }
	Vector2u GetSize() { return _pTex->getSize(); }
	Vector2f GetPosition() { return _position; }
	Vector2f GetAcceleration() { return _acceleration; }
	Vector2f GetVelocity() { return _velocity; }
	FloatRect GetBounds() { return _pSpr->getGlobalBounds(); }
	void AddAcceleration(Vector2f acc) {
		_acceleration.x += acc.x;
		_acceleration.y += acc.y;
	}

	
protected:

	Sprite* _pSpr;
	Texture* _pTex;
	Vector2f _position;
	Vector2f _acceleration;
	Vector2f _velocity;
	float _rotation;
};


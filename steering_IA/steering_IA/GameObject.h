#pragma once
#include "Vector3.h"
#include "SFML\Graphics.hpp"
class GameObject
{
public:
	Vector3 m_position;
	virtual void initialize();
	virtual void update();
	virtual void render();
	virtual void destroy();
	void setPosition(unsigned short x, unsigned short y);
	GameObject();
	~GameObject();
};

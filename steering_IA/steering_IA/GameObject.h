#pragma once
#include "Vector3.h"
class GameObject
{
public:
	Vector3 m_position;
	virtual void initialize();
	virtual void update();
	virtual void render();
	virtual void destroy();
	GameObject();
	~GameObject();
};

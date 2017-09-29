#pragma once
#include "GameObject.h"
class Obstacle : public GameObject
{
public:
	float m_radius;
	void initialize();
	void update();
	void render();
	void destroy();
	Obstacle();
	~Obstacle();
};


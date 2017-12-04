#pragma once
#include "SpriteRenderer.h"
using sf::CircleShape;

class Obstacle : public SpriteRenderer
{
public:
	CircleShape m_collider;
	float m_radius;
	void initialize();
	void update();
	void render(sf::RenderWindow& wnd);
	void setRadius(float radius);
	void destroy();
	Obstacle();
	~Obstacle();
};


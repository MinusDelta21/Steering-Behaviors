#pragma once
#include "SpriteRenderer.h"
class GameWindow;

class Bullet: public SpriteRenderer
{
public:
	GameWindow* m_gmScn;
	void init();
	void update();
	void render(RenderWindow& wnd);
	void destroy();

	unsigned int		m_team;
	Vector3			m_direction;

	static const int	BULLET_RADIUS = 15;
	static const int	BULLET_SPEED = 400;

	Bullet(Vector3& position, Vector3& direction, GameWindow* gmscn, unsigned int team = TEAM::Undefined);
	~Bullet();
};


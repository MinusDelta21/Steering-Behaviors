#include "stdafx.h"
#include "Bullet.h"
#include "Obstacle.h"
#include <vector>
#include "GameWindow.h"
using std::vector;

void Bullet::init()
{
	if (m_team == TEAM::Red) {
		setSprite("Sprites/red_bullet.jpg");
	}
	else {
		setSprite("Sprites/blue_bullet.jpg");
	}
	m_direction.normalize();
}

void Bullet::update()
{
	
	m_position = m_position + m_direction * BULLET_SPEED * m_gmScn->m_wndTime.getFrameTime();
	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation(m_direction.deg2rad());

	//Busqueda de objetos
	vector<Obstacle*> obs = m_gmScn->getObjsInArea<Obstacle>(m_position.x, m_position.y, 200);
	for (auto obstacle : obs)
	{
		Vector3 distToObs = obstacle->m_position - m_position;
		if ((distToObs.magnitud() - (obstacle->m_radius * 0.5)) <= BULLET_RADIUS)
		{
			m_gmScn->destroyObject(this);
			return;
		}
	}

	if (m_position.x < 0 || m_position.x > 1920 || m_position.y < 0 || m_position.y > 1080)
	{
		m_gmScn->destroyObject(this);
		return;
	}
	return;
}

void Bullet::render(RenderWindow & wnd)
{
	if (m_visible) {
		wnd.draw(m_sprite);
	}
}

void Bullet::destroy()
{
}

Bullet::Bullet(Vector3 & position, Vector3 & direction, GameWindow * gmscn, unsigned int team)
{
	m_position = position;
	init();
}

Bullet::~Bullet()
{
}

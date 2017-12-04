#include "stdafx.h"
#include "Flag.h"


void Flag::init()
{
	if (m_team == TEAM::Red)
	{
		this->setSprite("Sprites/red_flag.png");
	}
	else if (m_team == TEAM::Blue)
	{
		this->setSprite("Sprites/Blue_flag_detail.png");
	}
	else
	{
		this->setSprite("Sprites/Blue_flag_detail.png");
	}
	this->setColor(Vector3(255.f, 255.f, 255.f), 255.f);
}

void Flag::render(RenderWindow & wnd)
{
	wnd.draw(m_sprite);
}

Flag::Flag(unsigned short team)
{
	m_team = team;
	if (m_team == 1) m_tag = "Blue Flag";
	else if (m_team == 2) m_tag = "Red Flag";
	else m_tag = m_team;
	m_radius = 10;
	init();
}


Flag::~Flag()
{
}

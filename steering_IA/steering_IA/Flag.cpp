#include "stdafx.h"
#include "Flag.h"


void Flag::init()
{
	if (m_team == TEAM::Red)
	{
		this->setSprite("Sprites/red-39392_640.png");
	}
	else if (m_team == TEAM::Green)
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
	m_radius = 10;
	init();
}


Flag::~Flag()
{
}

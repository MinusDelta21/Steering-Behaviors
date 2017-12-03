#include "stdafx.h"
#include "Flag.h"


void Flag::init()
{
	if (m_team == TEAM::Red)
	{
		this->setSprite("	spr_red_flag.png");
	}
	else if (m_team == TEAM::Green)
	{
		this->setSprite("gameResources/sprites/spr_green_flag.png");
	}
	else
	{
		this->setSprite("gameResources/sprites/spr_green_flag.png");
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

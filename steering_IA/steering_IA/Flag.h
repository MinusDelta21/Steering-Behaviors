#pragma once
#include "SpriteRenderer.h"
class Flag :
	public SpriteRenderer
{

public:
	unsigned short	m_radius;
	unsigned short	m_team;
	void init();
	void render(RenderWindow& wnd);
	Flag(unsigned short team);
	~Flag();
};
#pragma once
#include "World.h"
class Application
{
	World m_world;
public:
	void initialize();
	void update();
	void render();
	void destroy();
	Application();
	~Application();
};


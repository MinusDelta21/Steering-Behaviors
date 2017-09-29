#pragma once
#include "GameObject.h"
#include <vector>
class World
{
	std::vector<GameObject> m_gameObjects;
public:
	void initialize();
	void update();
	void render();
	void destroy();
	World();
	~World();
};


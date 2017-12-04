#include "stdafx.h"
#include "World.h"
#include <iostream>
using std::iostream;
void World::initialize() {

}
void World::update() {
	for (unsigned int i = 0; i < m_obsToDelete.size(); ++i)
	{
		for (unsigned int j = 0; j < m_gameObjects.size(); ++j)
		{
			if (m_gameObjects[j] != nullptr)
			{
				if (m_gameObjects[j] == m_obsToDelete[i])
				{
					delete m_gameObjects[j];
					m_obsToDelete[i] = nullptr;
					m_gameObjects[j] = nullptr;
					m_gameObjects.erase(m_gameObjects.begin() + j);
					break;
				}					
			}
		}
	}
	m_obsToDelete.clear();

	for (unsigned int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (m_gameObjects[i] != nullptr)
		{
			m_gameObjects[i]->update();
		}		
	}	
}
void World::render(RenderWindow& wnd) {
	for (unsigned int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (m_gameObjects[i] != nullptr)
		{
			m_gameObjects[i]->render(wnd);
		}
	}
}
void World::destroy() {
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (m_gameObjects[i] != nullptr)
		{
			delete m_gameObjects[i];
		}
	}
	m_gameObjects.clear();
}
void World::addGameObject(GameObject * newGameObject)
{
	for (unsigned int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (newGameObject->m_layer < m_gameObjects[i]->m_layer)
		{
			std::cout << "GO Added: "<< std::endl;
			m_gameObjects.insert(m_gameObjects.begin() + i, newGameObject);
			return;
		}
	}
	std::cout << "GO Added: " << std::endl;
	m_gameObjects.push_back(newGameObject);
	return;
}
bool World::destroyGameObject(GameObject * gameObject)
{
	m_obsToDelete.push_back(gameObject);
	return false;
}
World::World()
{

}


World::~World()
{
	destroy();
}

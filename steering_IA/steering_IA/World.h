#pragma once
#include "GameObject.h"
#include "Boid.h"
#include <vector>
using std::vector;
class World
{
	vector<GameObject*> m_gameObjects;
	vector<GameObject*> m_obsToAdd;
	vector<GameObject*> m_obsToDelete;
public:
	void initialize();
	void update();
	void render(RenderWindow& wnd);
	void destroy();
	void		addGameObject(GameObject* newGameObject);
	bool		destroyGameObject(GameObject* gameObject);
	template <class _obj> vector<_obj*>	getObjsInArea(int x, int y, float radius, unsigned int m_group = GOGROUP::kEverything);
	template <class _obj> vector<_obj*> getObjs(unsigned int m_group = GOGROUP::kEverything);
	World();
	~World();
};

template<class _obj>
inline vector<_obj*> World::getObjsInArea(int x, int y, float radius, unsigned int m_group)
{
	Vector3 position((float)x, (float)y);
	vector<_obj*> objectsDetected;

	for (unsigned int i = 0; i < m_gameObjects.size(); ++i) {
		if ((position - m_gameObjects[i]->m_position).magnitud() <= radius)
		{
			_obj* object = dynamic_cast<_obj*>(m_gameObjects[i]);
		}
	}
	return objectsDetected;
}

template<class _obj>
inline vector<_obj*> World::getObjs(unsigned int m_group)
{
	vector<_obj*> objects;
	for (unsigned int i = 0; i < m_gameObjects.size(); ++i)
	{
		_obj* object = dynamic_cast<_obj*>(m_gameObjects[i]);
	}
	return objects;
}
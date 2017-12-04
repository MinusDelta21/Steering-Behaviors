#pragma once
#include "Window.h"
#include "World.h"
#include "App.h"
class World;
class GameWindow: public Window
{
public:
	World m_world;
	Boid* m_activeAgent;

	virtual void	onEnter();
	virtual void	onExit();

	virtual void init();
	virtual unsigned int update(void* pObject);
	virtual void render();
	virtual void destroy();
	bool		 destroyObject(GameObject* obj);
	void		 addNewObject(GameObject* obj);
	template <class _obj> vector<_obj*>	getObjsInArea(int x, int y, float radius, unsigned int group = GOGROUP::kEverything);
	template <class _obj> vector<_obj*> getObjs(unsigned int group = GOGROUP::kEverything);

	GameWindow(int sceneID, const std::string& title, Application* app) : Window(sceneID, title, app) {}
	virtual ~GameWindow();
	~GameWindow();
};

template<class _obj>
inline vector<_obj*> GameWindow::getObjsInArea(int x, int y, float radius, unsigned int group)
{
	return m_world.getObjsInArea<_obj>(x, y, radius, group);
}

template<class _obj>
inline vector<_obj*> GameWindow::getObjs(unsigned int group)
{
	return m_world.getObjs<_obj>(group);
}

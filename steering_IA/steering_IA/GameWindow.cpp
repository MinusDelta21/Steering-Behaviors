#include "stdafx.h"
#include "GameWindow.h"


GameWindow::~GameWindow()
{
	destroy();
}

void GameWindow::onEnter()
{
	init();
}

void GameWindow::onExit()
{
	destroy();
}

void GameWindow::init()
{
	m_world.initialize();
	m_wndTime.init();

}

unsigned int GameWindow::update(void * pObject)
{
	m_wndTime.update();
	m_world.update();

	return 0;
}

void GameWindow::render()
{
	m_world.render(m_window);
}

void GameWindow::destroy()
{
	m_wndTime.destroy();
	m_world.destroy();
}

bool GameWindow::destroyObject(GameObject * obj)
{
	return m_world.destroyGameObject(obj);
}

void GameWindow::addNewObject(GameObject * obj)
{
	m_world.addGameObject(obj);

}

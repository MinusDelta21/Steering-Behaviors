#include "stdafx.h"
#include "MainMenu.h"


void MainMenu::initialize()
{
	MainButton* GameButton = new MainButton();
	GameButton->setPosition(400, 260);
	GameButton->init();
	m_buttonList.push_back(GameButton);
}

void MainMenu::update()
{
	for (unsigned int i = 0; i < m_buttonList.size(); ++i)
		m_buttonList[i]->update();
}

void MainMenu::render(RenderWindow & wnd)
{
	for (unsigned int i = 0; i < m_buttonList.size(); ++i)
		m_buttonList[i]->render(wnd);
}

void MainMenu::destroy()
{
	for (unsigned int i = 0; i < m_buttonList.size(); ++i)
		m_buttonList[i]->destroy();
}

MainMenu::MainMenu()	
{
}


MainMenu::~MainMenu()
{
}

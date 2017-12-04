#include "stdafx.h"
#include "GameWindow.h"
#include "Agent.h"

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
	initialize(1920, 1080, "Capture The Flag 2");
	m_world.initialize();
	m_wndTime.init();
	//OBSTACLES
	vector<Obstacle*> mapObstacles;
	Obstacle* obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(75.f);
	obs->setPosition(960, 540);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(1310, 540);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(610, 540);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(515, 262);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(515, 818);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(1405, 262);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(1405, 818);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(960, 180);
	obs->setScale(0.5f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(960, 900);
	obs->setScale(0.5f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(37.f);
	obs->setPosition(890, 230);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(37.f);
	obs->setPosition(830, 285);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(37.f);
	obs->setPosition(770, 335);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(37.f);
	obs->setPosition(770, 735);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(37.f);
	obs->setPosition(1150, 335);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(37.f);
	obs->setPosition(1150, 735);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(1665, 335);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(1665, 735);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(255, 335);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	obs = new Obstacle();
	obs->setSprite("Sprites/orange-circle-md.png");
	obs->setRadius(50.f);
	obs->setPosition(255, 735);
	obs->setScale(0.3f);
	m_world.addGameObject(obs);

	static const int offsetField = 100;
	//INVISIBLE OBSTACLES
	for (int i = 0; i < 13; ++i)
	{
		obs = new Obstacle();
		obs->setRadius(150);
		obs->setPosition(i * 150, -offsetField);
		obs->m_visible = false;
		m_world.addGameObject(obs);
	}

	for (int i = 0; i < 14; ++i)
	{
		obs = new Obstacle();
		obs->setRadius(150.f);
		obs->setPosition(i * 150, 1080 + offsetField);
		obs->m_visible = false;
		m_world.addGameObject(obs);
	}

	for (int i = 0; i < 7; ++i)
	{
		obs = new Obstacle();
		obs->setRadius(150.f);
		obs->setPosition(0 - offsetField, i * 150);
		obs->m_visible = false;
		m_world.addGameObject(obs);
	}

	for (int i = 0; i < 7; ++i)
	{
		obs = new Obstacle();
		obs->setRadius(150.f);
		obs->setPosition(1920 + offsetField, i * 150);
		obs->m_visible = false;
		m_world.addGameObject(obs);
	}

	Flag* _newFlag = new Flag(TEAM::Red);
	_newFlag->setPosition(200, 540);
	_newFlag->setScale(0.2f);
	m_world.addGameObject(_newFlag);

	_newFlag = new Flag(TEAM::Blue);
	_newFlag->setPosition(1720, 540);
	_newFlag->setScale(0.3f);
	m_world.addGameObject(_newFlag);


	unsigned short teamSize = 5;
	const unsigned short yOffset = (1080 - 200) / teamSize;
	unsigned short currOffset = yOffset;
	Agent* redTeam;
	Agent* blueTeam;
	for (int i = 0; i < teamSize+1; ++i) {
		//Create Agent
		redTeam = new Agent(this, TEAM::Red);
		blueTeam = new Agent(this, TEAM::Blue);
		//Set Agent Scale
		redTeam->setScale(0.18);
		blueTeam->setScale(0.1);
		//Set Agent Position
		redTeam->setPosition(400, currOffset);
		blueTeam->setPosition(1560, currOffset);
		//Set respawn Position
		redTeam->m_respawnPosition = redTeam->m_position;
		blueTeam->m_respawnPosition = blueTeam->m_position;
		//Set Velocity
		redTeam->setVelocity(100.f);
		blueTeam->setVelocity(100.f);
		//Add objects to World
		m_world.addGameObject(redTeam);
		m_world.addGameObject(blueTeam);

		currOffset = yOffset + (yOffset* i);
	}
}

unsigned int GameWindow::update(void * pObject)
{
	m_wndTime.update();
	m_world.update();

	return 0;
}

void GameWindow::render()
{
	RenderWindow* ptrWin = &m_window;
	m_world.render(m_window);
	m_window.display();
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

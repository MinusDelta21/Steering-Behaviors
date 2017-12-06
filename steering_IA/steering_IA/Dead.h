#pragma once
#include "BaseState.h"
class BaseAgent;
class Agent;
class Dead : public BaseAgent
{
public:
	static const int m_respawnTime = 5;
	float m_time;
	void onEnter();
	unsigned int update(void* pObject);
	void onExit();

	Dead(Agent* mySoldier):BaseAgent(BOIDSTATE::Dead, mySoldier){}
	~Dead();
};


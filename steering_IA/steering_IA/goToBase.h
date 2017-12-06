#pragma once
#include "BaseState.h"
class Agent;

class goToBase:public BaseAgent
{
public:
	void onEnter();
	unsigned int update(void* pObject);
	void onExit();
	goToBase(Agent* mySoldier) : BaseAgent(BOIDSTATE::Idle, mySoldier) {}
	~goToBase();
};


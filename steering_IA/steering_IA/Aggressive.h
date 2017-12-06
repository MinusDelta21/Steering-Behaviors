#pragma once
#include "BaseState.h"
class Agent;
class BaseAgent;
class Aggressive : public BaseAgent 
{
public:
	void onEnter();
	unsigned int update(void* pObject);
	void onExit();
	Aggressive(Agent* mySoldier) : BaseAgent(BOIDSTATE::Attack, mySoldier){}
	~Aggressive();
};


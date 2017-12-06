#pragma once
#include "BaseState.h"
class Agent;
class DefendCaptured :
	public BaseAgent
{
public:
	void onEnter();
	unsigned int update(void* pObject);
	void onExit();
	DefendCaptured(Agent * mySoldier) :BaseAgent(BOIDSTATE::DefendLeader, mySoldier){}
	~DefendCaptured();
};


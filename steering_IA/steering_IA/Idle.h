#pragma once
#include "BaseState.h"
class Agent;
class Idle :
	public BaseAgent
{
public:
	void onEnter();
	unsigned int update(void* pObject);
	void onExit();
	Idle(Agent* mySoldier) : BaseAgent(BOIDSTATE::Idle, mySoldier){}
	~Idle();

};


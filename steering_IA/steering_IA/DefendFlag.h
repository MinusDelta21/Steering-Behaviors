#pragma once
#include "BaseState.h"
class DefendFlag :
	public BaseAgent
{
	static const int DEFENCE_RANGE = 560;
public:
	void onEnter();
	unsigned int update(void* pObject);
	void onExit();
	DefendFlag(Agent* mySoldier) : BaseAgent(BOIDSTATE::DefendBase, mySoldier){}
	~DefendFlag();
};


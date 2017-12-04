#pragma once
#include "BaseState.h"
class Attack :
	public BaseAgent
{
public:
	Agent* m_enemy;
	void onEnter();
	unsigned int update(void* pObject);
	void onExit();
	Attack(Agent* mySoldier) : BaseAgent(BOIDSTATE::AttackEnemy, mySoldier){}
	~Attack();
};


#pragma once
#include "State.h"
class Agent;
class BaseAgent :public State
{
public:
	Agent*	m_agent;
	virtual void onEnter();
	virtual unsigned int update(void* pObject);
	virtual void onExit();
	BaseAgent(int id, Agent* myBoid) : State(id), m_agent(myBoid) {}
	virtual ~BaseAgent();
};


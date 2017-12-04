#pragma once
#include <vector>
#include "State.h"
using std::vector;
class State;
class StateMachine
{
public:
	vector<State*>m_stateList;
	State* m_state;
	void AddState(State* pState, bool deleteOnExit = true);
	int SetState(unsigned int s);
	int UpdateState(void* pObject);
	StateMachine();
	~StateMachine();
};


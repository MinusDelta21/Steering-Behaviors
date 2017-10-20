#pragma once
#include <vector>
#include "State.h"
using std::vector;
class StateMachine
{
	vector<State>m_stateList;
public:
	void update();
	StateMachine();
	~StateMachine();
};


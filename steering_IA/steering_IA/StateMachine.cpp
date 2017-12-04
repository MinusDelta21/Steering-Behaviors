#include "stdafx.h"
#include "StateMachine.h"




void StateMachine::AddState(State * pState, bool deleteOnExit)
{
	if (pState)
	{
		m_stateList.push_back(pState);
		pState->SetFSM(this);
	}
}

int StateMachine::SetState(unsigned int s)
{
	for (auto& state : m_stateList)
	{
		if (state->m_id == s)
		{
			if (m_state != state) {
				if (m_state != nullptr) {
					m_state->onExit();
				}
				m_state = state;
				m_state->onEnter();
			}

			return m_state->m_id;
		}
	}

	return 0;
}

int StateMachine::UpdateState(void * pObject)
{
	if (m_state)
	{
		return m_state->update(pObject);
	}
	return 0;
}

StateMachine::StateMachine()
{
	m_state = nullptr;

}


StateMachine::~StateMachine()
{
	m_state = nullptr;

	for (auto state : m_stateList)
	{
		delete state;
	}

	m_stateList.clear();
}

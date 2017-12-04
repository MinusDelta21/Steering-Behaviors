#pragma once
class StateMachine;
class State
{

public:
	unsigned int m_id;
	StateMachine* m_pFSM;

	virtual void onEnter();
	virtual unsigned int update(void* pObject);
	virtual void onExit();

	State(unsigned int id) : m_id(id), m_pFSM(nullptr) {}
	virtual ~State();

	void SetFSM(StateMachine* pFSM) {
		m_pFSM = pFSM;
	}
};


#include "FinateStateMachine.h"

FinateState::FinateState()
{
	m_mapOutput.clear();
}

void FinateState::AddTransition(const E_EVENT& eventtype, const std::string& statetype)
{
	m_mapOutput[eventtype] = statetype;
}
std::string FinateState::GetState(const E_EVENT& eventtype)
{
	return m_mapOutput[eventtype];
}

void * FinateState::operator new(size_t sz, const char* FileName, int iLine)
{
	std::string ad = FileName;
	MEMINFO mem;
	void* pfs = new char[sz];
	mem.addr = pfs;
	mem.filename = ad.substr(ad.find_last_of('\\') + 1, ad.length() - (ad.find_last_of(".cpp") + 4));
	mem.line = iLine;
	mem.dwAllocateTime = timeGetTime();
	MemoryMap.insert(std::make_pair(pfs, mem));
	++::g_iNewCount;
	return pfs;
}
void FinateState::operator delete(void * p)
{
	std::map<void*, MEMINFO>::iterator it;
	it = MemoryMap.find(p);
	MemoryMap.erase(it);
	--::g_iNewCount;
	delete p;
}
FinateStateMachine::FinateStateMachine()
{
	m_mapState.clear();
	AddStateTransition(std::string("Move"), E_EVENT::FINDTARGET, std::string("Chase"));
	AddStateTransition(std::string("Chase"), E_EVENT::INATTACKRANGE, std::string("Attack"));
	AddStateTransition(std::string("Chase"), E_EVENT::BEATTACKED, std::string("Hit"));
	AddStateTransition(std::string("Chase"), E_EVENT::LOSTTARGET, std::string("Move"));
	AddStateTransition(std::string("Attack"), E_EVENT::OUTATTACKRANGE, std::string("Chase"));
	AddStateTransition(std::string("Attack"), E_EVENT::BEATTACKED, std::string("Hit"));
	AddStateTransition(std::string("Move"), E_EVENT::BEATTACKED, std::string("Hit"));
	AddStateTransition(std::string("Hit"), E_EVENT::NOHIT, std::string("Chase"));
}
FinateStateMachine::~FinateStateMachine()
{
	for (auto it : m_mapState)
	{
		delete it.second;
		m_mapState.erase(it.first);
	}
}
void FinateStateMachine::AddStateTransition(const std::string& inputState,
						const E_EVENT& eventtype, const std::string& outputState)
{
	FinateState * nstate = nullptr;
	EnemyIterator iter = m_mapState.find(inputState);
	if (iter == m_mapState.end())
	{
		nstate = New FinateState;
		m_mapState[inputState] = nstate;
	}
	else
	{
		nstate = iter->second;
	}
	nstate->AddTransition(eventtype, outputState);
}
std::string FinateStateMachine::StateTransition(const std::string& currentstate, const E_EVENT& eventtype)
{
	return m_mapState[currentstate]->GetState(eventtype);
}

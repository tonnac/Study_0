#include "ZFsmMgr.h"

int ZFsmMgr::Load(T_STR szLoadFile)
{
	ZFiniteStateMachine * pfsm = new ZFiniteStateMachine;
	if (pfsm->LoadFile(szLoadFile))
	{
		m_map.insert(std::make_pair(++m_iIndex, pfsm));
		return m_iIndex;
	}
	return -1;
}
ZFiniteStateMachine * ZFsmMgr::getPtr(int iKey)
{
	std::map<int, ZFiniteStateMachine*>::iterator iter;
	iter = m_map.find(iKey);
	if (iter == m_map.end())
	{
		return nullptr;
	}
	return static_cast<ZFiniteStateMachine*>(iter->second);
}
int	ZFsmMgr::getSize()
{
	return m_map.size();
}
ZFsmMgr::ZFsmMgr() : m_iIndex(0)
{
}


ZFsmMgr::~ZFsmMgr()
{
}

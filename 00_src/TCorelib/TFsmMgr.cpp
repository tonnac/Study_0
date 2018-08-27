#include "TFsmMgr.h"
int	TFsmMgr::Load(T_STR szLoadFile)
{
	T_STR szName = szLoadFile;

	std::map<int, TFiniteStateMachine*>::iterator iter;
	for (iter = m_mapList.begin();
		iter != m_mapList.end();
		iter++)
	{
		TFiniteStateMachine* pData = (TFiniteStateMachine*)(*iter).second;
		if (pData->m_szName == szName)
		{
			return (*iter).first;
		}
	}
	TFiniteStateMachine* pData = new TFiniteStateMachine;
	if (pData->Load(szLoadFile))
	{
		m_mapList.insert(std::make_pair(++m_iInex, pData));
		return m_iInex;
	}
	return -1;
}
TFiniteStateMachine* TFsmMgr::GetPtr(int iKey)
{
	std::map<int, TFiniteStateMachine*>::iterator iter;
	iter = m_mapList.find(iKey);
	if (iter == m_mapList.end())
		return NULL;
	return (*iter).second;
}
bool TFsmMgr::Release()
{
	std::map<int, TFiniteStateMachine*>::iterator iter;
	for (iter = m_mapList.begin();
		iter != m_mapList.end();
		iter++)
	{
		TFiniteStateMachine* pData = (TFiniteStateMachine*)(*iter).second;
		delete pData;
	}
	m_mapList.clear();
	return true;
}



TFsmMgr::TFsmMgr()
{
	m_iInex = 0;
}


TFsmMgr::~TFsmMgr()
{
	Release();
}

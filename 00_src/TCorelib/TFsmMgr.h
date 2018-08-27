#pragma once
#include "TFiniteStateMachine.h"
class TFsmMgr : public TSingleton<TFsmMgr>
{
	friend class TSingleton<TFsmMgr>;
	std::map<int, TFiniteStateMachine*> m_mapList;
	int		m_iInex;
public:
	int   Size() { return m_mapList.size(); }
	int	Load(T_STR szLoadFile);
	bool Release();
	TFiniteStateMachine*  GetPtr(int iKey);
protected:
	TFsmMgr();
public:
	virtual ~TFsmMgr();
};
#define I_fsmMgr TFsmMgr::GetInstance()


#pragma once
#include "ZFiniteStateMachine.h"

class ZFsmMgr : public Singleton<ZFsmMgr>
{
	friend class Singleton<ZFsmMgr>;
private:
	ZFsmMgr();
public:
	virtual ~ZFsmMgr();
public:
	bool								Release();
	int									getSize();
	int									Load(T_STR szLoadFile);
	ZFiniteStateMachine *				getPtr(int iKey);
private:
	int									m_iIndex;
	std::map<int, ZFiniteStateMachine*>	m_map;
};

#define I_ZFsmMgr ZFsmMgr::getInstance()



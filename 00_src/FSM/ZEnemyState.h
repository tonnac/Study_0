#pragma once
#include "KObject.h"

class ZEnemy;

class ZEnemyState
{
protected:
	ZEnemy * m_pOwner;
public:
	virtual bool Process(KObject * pTarget) = 0;
public:
	ZEnemyState(ZEnemy * pParent);
	virtual ~ZEnemyState();
};


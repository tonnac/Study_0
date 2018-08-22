#pragma once
#include "Object.h"

class ZEnemy;

class ZEnemyState
{
protected:
	ZEnemy * m_pOwner;
public:
	virtual bool Process(Object * pTarget) = 0;
public:
	ZEnemyState(ZEnemy * pParent);
	virtual ~ZEnemyState();
};


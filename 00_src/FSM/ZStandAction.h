#pragma once
#include "Enemy.h"

class ZStandAction : public ZEnemyState
{
public:
	bool Process(Object * pTarget) override;
public:
	ZStandAction(ZEnemy * pOwner);
	virtual ~ZStandAction();
};


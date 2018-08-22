#pragma once
#include "Enemy.h"
#include "ZEnemyState.h"

class ZAttackAction : public ZEnemyState
{
public:
	bool Process(Object * pTarget) override;
public:
	ZAttackAction(ZEnemy * pOwner);
	virtual ~ZAttackAction();
};


#pragma once
#include "ZEnemy.h"

class ZAttackAction : public ZEnemyState
{
public:
	bool Process(KObject * pTarget) override;
public:
	ZAttackAction(ZEnemy * pOwner);
	virtual ~ZAttackAction();
};


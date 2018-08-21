#pragma once
#include "ZEnemy.h"

class ZStandAction : public ZEnemyState
{
public:
	bool Process(KObject * pTarget) override;
public:
	ZStandAction(ZEnemy * pOwner);
	virtual ~ZStandAction();
};


#pragma once
#include "State.h"

class EffectObj;
class Enemy;

class EnemyBasicState : public State
{
public:
	EnemyBasicState(Enemy*);
public:
	virtual bool		Init() = 0;
	virtual bool		Frame() = 0;
	virtual bool		Render() override;
	bool				Release();
};

class EnemyMoveState : public EnemyBasicState
{
public:
	EnemyMoveState(Enemy*);
public:
	bool				Init();
	bool				Frame();
};

class EnemyAttackState : public EnemyBasicState
{
public:
	EnemyAttackState(Enemy*);
public:
	bool				Init();
	bool				Frame();
};

class EnemyHitState : public EnemyBasicState
{
public:
	EnemyHitState(Enemy*);
public:
	bool				Init();
	bool				Frame();
};
#pragma once
#include "PlayerBasicState.h"

class PlayerAttack : public PlayerState
{
public:
	PlayerAttack(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
};

class PlayerAttack2 : public PlayerState
{
public:
	PlayerAttack2(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
};

class PlayerAttack3 : public PlayerState
{
public:
	PlayerAttack3(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
};

class AirAttack : public PlayerState
{
public:
	AirAttack(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
private:
	FLOAT		m_fAcceleration;
};
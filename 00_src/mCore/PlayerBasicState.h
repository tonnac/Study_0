#pragma once
#include "State.h"
#include "Player.h"

class EffectObj;

class PlayerState : public State
{
public:
	PlayerState(Player*);
public:
	virtual bool		Init() =0;
	virtual bool		Frame() =0;
	virtual	bool		Render();
	virtual	bool		Release();
protected:
	EffectObj *			m_pEffectObj;
	FLOAT				m_fTimer;
};

class PlayerIdle : public PlayerState
{
public:
	PlayerIdle(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
};

class PlayerRun : public PlayerState
{
public:
	PlayerRun(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
};

class PlayerBrake : public PlayerState
{
public:
	PlayerBrake(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
};

class PlayerTurn : public PlayerState
{
public:
	PlayerTurn(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
};

class PlayerJump : public PlayerState
{
public:
	PlayerJump(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
private:
	FLOAT		m_fJumpSpeed;
	FLOAT		m_fAcceleration;
};

class PlayerJump2 : public PlayerState
{
public:
	PlayerJump2(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
private:
	FLOAT		m_fJumpSpeed;
	FLOAT		m_fAcceleration;
};

class PlayerFall : public PlayerState
{
public:
	PlayerFall(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
private:
	FLOAT		m_fAcceleration;
};

class PlayerRise : public PlayerState
{
public:
	PlayerRise(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
};
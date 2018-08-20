#include "PlayerBasicState.h"
#include "EffectObj.h"

#include "TerrainObject.h"

PlayerState::PlayerState(Player * pPlayer) : State(pPlayer), m_pEffectObj(nullptr), m_fTimer(0.0f)
{}
bool PlayerState::Render()
{
	return true;
}
bool PlayerState::Release()
{
	if (m_pEffectObj)
	{
		m_pEffectObj->Release();
		delete m_pEffectObj;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerIdle::PlayerIdle(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Idle"), this);
}
bool PlayerIdle::Init()
{
	setSprite(L"Kaho", L"Idle");
	m_pSprite->setDivideTime(1.8f);
	return true;
}
bool PlayerIdle::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	FLOAT fSPeed = m_pPlayer->getSpeed();
	m_CenterPos->y += g_fPerSecFrame * 30.0f;
	if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH)
	{
		m_pPlayer->setState(L"Jump");
		return true;
	}
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == -1)		// 방향 같으면
		{
			m_pPlayer->setState(L"Run");
			return true;
		}
		else								// 방향 다르면
		{
			m_pPlayer->setState(L"Turn");
			return true;
		}
	}
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == 1)
		{
			m_pPlayer->setState(L"Run");
			return true;
		}
		else
		{
			m_pPlayer->setState(L"Turn");
			return true;
		}
	}
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pPlayer->setState(L"Attack1");
		return true;
	}
	if (!m_pSprite->Frame())				// 한바퀴 다돌면
	{
		m_pSprite->setIndex(0);
	}
	*(m_rtDraw) = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerRun::PlayerRun(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Run"), this);
}
bool PlayerRun::Init()
{
	setSprite(L"Kaho", L"Run");
	m_pSprite->setDivideTime(1.8f);
	return true;
}
bool PlayerRun::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);

	FLOAT fSpeed = m_pPlayer->getSpeed();
	m_CenterPos->y += g_fPerSecFrame * 2.0f;
	if (!m_pPlayer->getLanding())
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Fall");
		return true;
	}

	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Attack1");
		return true;
	}
	if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH || S_Input.GetKey('A') == KEYSTATE::KEY_HOLD)
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Jump");
		return true;
	}
	if ((m_pPlayer->getDir() == 1 && (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD))
		|| (m_pPlayer->getDir() == -1 && (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)))
	{
		FLOAT fSpeed = m_pPlayer->getSpeed();
		m_CenterPos->x += m_pPlayer->getDir() * g_fPerSecFrame * fSpeed;
		*m_rtDraw = m_pSprite->getSpriteRt();
	}
	else if ((S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE) ||
		(S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_FREE))
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Brake");
		return true;
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(2);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerBrake::PlayerBrake(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Brake"), this);
}
bool PlayerBrake::Init()
{
	setSprite(L"Kaho", L"Brake");
	m_pSprite->setDivideTime(0.7f);
	return true;
}
bool PlayerBrake::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE)
	{
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Idle");
		return true;
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerTurn::PlayerTurn(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Turn"), this);
}
bool PlayerTurn::Init()
{
	setSprite(L"Kaho", L"Turn");
	m_pSprite->setDivideTime(0.3f);
	return true;
}
bool PlayerTurn::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	if (!m_pSprite->Frame())
	{
		m_pPlayer->setDir(-1);
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Run");
		return true;
	}
	if (m_pPlayer->getDir() == 1)
	{
		m_pPlayer->setRendering(INVERSE::LR_ROTATION);
	}
	else
	{
		m_pPlayer->setRendering(INVERSE::DEFAULT);
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerJump::PlayerJump(Player * pPlayer) : PlayerState(pPlayer), m_fJumpSpeed(270.0f), m_fAcceleration(5.5f)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Jump"), this);
}
bool PlayerJump::Init()
{
	setSprite(L"Kaho", L"Jump");
	m_pSprite->setDivideTime(1.0f);
	return true;
}
bool PlayerJump::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	INT iJumpNumber = m_pPlayer->getJumpNum();

	m_pPlayer->setLanding(false);

	m_fTimer += g_fPerSecFrame;

	m_fJumpSpeed -= m_fAcceleration;
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_fJumpSpeed = 270.0f;
		m_pPlayer->setState(L"AirAttack");
		return true;
	}
	if (m_fJumpSpeed < 0.0f)
	{
		m_fJumpSpeed = 270.0f;
		m_pPlayer->setState(L"Fall");
		return true;
	}
	m_CenterPos->y -= g_fPerSecFrame * m_fJumpSpeed;
	if (iJumpNumber == 0 && (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH))
	{
		m_fJumpSpeed = 250.f;
		m_pPlayer->setJumpNum(1);
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Jump2");
		return true;
	}
	FLOAT fSpeed = m_pPlayer->getSpeed();
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->x += g_fPerSecFrame * fSpeed;
	}
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->x -= g_fPerSecFrame * fSpeed;
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerJump2::PlayerJump2(Player * pPlayer) : PlayerState(pPlayer), m_fJumpSpeed(200.0f), m_fAcceleration(3.5f)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Jump2"), this);
}
bool PlayerJump2::Init()
{
	setSprite(L"Kaho", L"Jump");
	m_pSprite->setDivideTime(1.0f);
	return true;
}
bool PlayerJump2::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	INT iJumpNumber = m_pPlayer->getJumpNum();

	m_CenterPos->y -= g_fPerSecFrame * m_fJumpSpeed;

	m_fJumpSpeed -= m_fAcceleration;
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_fJumpSpeed = 200.0f;
		m_pPlayer->setState(L"AirAttack");
		return true;
	}
	if (m_fJumpSpeed < 0.0f)
	{
		m_fJumpSpeed = 200.0f;
		m_pPlayer->setState(L"Fall");
		return true;
	}
	FLOAT fSpeed = m_pPlayer->getSpeed();
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->x += g_fPerSecFrame * fSpeed;
	}
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->x -= g_fPerSecFrame * fSpeed;
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerFall::PlayerFall(Player * pPlayer) : PlayerState(pPlayer), m_fAcceleration(3.5f)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Fall"), this);
}
bool PlayerFall::Init()
{
	setSprite(L"Kaho", L"Fall");
	m_pSprite->setDivideTime(0.5f);
	return true;
}
bool PlayerFall::Frame()
{
	m_fTimer += g_fPerSecFrame;
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	INT iJumpNum = m_pPlayer->getJumpNum();
	FLOAT fSpeed = m_pPlayer->getSpeed();
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pPlayer->setState(L"AirAttack");
		return true;
	}
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->x += g_fPerSecFrame * fSpeed;
	}
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->x -= g_fPerSecFrame * fSpeed;
	}

	m_CenterPos->y += g_fPerSecFrame + m_fAcceleration;

	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(2);
	}
	if (m_fTimer >= 0.1f && iJumpNum == 0 &&
		(S_Input.GetKey('A') == KEYSTATE::KEY_PUSH))
	{
		m_pPlayer->setJumpNum(1);
		m_pSprite->setIndex(0);
		m_fTimer = 0.0f;
		m_pPlayer->setState(L"Jump");
		return true;
	}
	if (m_pPlayer->getLanding())
	{
		m_pPlayer->setJumpNum(0);
		m_pSprite->setIndex(0);
		m_fTimer = 0.0f;
		m_pPlayer->setState(L"Rise");
		return true;
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerRise::PlayerRise(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Rise"), this);
}
bool PlayerRise::Init()
{
	setSprite(L"Kaho", L"Rise");
	m_pSprite->setDivideTime(0.3f);
	return true;
}
bool PlayerRise::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Idle");
		return true;
	}
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == -1)		// 방향 같으면
		{
			m_pPlayer->setState(L"Run");
			return true;
		}
	}
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == 1)
		{
			m_pPlayer->setState(L"Run");
			return true;
		}
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}
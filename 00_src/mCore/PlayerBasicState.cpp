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
	m_pCharObj->addState(std::string("Idle"), this);
}
bool PlayerIdle::Init()
{
	setSprite(L"Kaho", L"Idle");
	m_pSprite->setDivideTime(1.8f);
	return true;
}
bool PlayerIdle::Frame()
{
	m_CenterPos->y += g_fPerSecFrame * 30.0f;
	if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH)
	{
		m_pCharObj->setState(L"Jump");
		return true;
	}
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pCharObj->getDir() == -1)		// 방향 같으면
		{
			m_pCharObj->setState(L"Run");
			return true;
		}
		else								// 방향 다르면
		{
			m_pCharObj->setState(L"Turn");
			return true;
		}
	}
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pCharObj->getDir() == 1)
		{
			m_pCharObj->setState(L"Run");
			return true;
		}
		else
		{
			m_pCharObj->setState(L"Turn");
			return true;
		}
	}
	if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH && m_pCharObj->getLadder())
	{
		m_pCharObj->setState(L"LadderEnter");
		return true;
	}
	if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH && m_pCharObj->getLadder())
	{
		m_pCharObj->setState(L"LadderUp");
		return true;
	}
	if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_HOLD)
	{
		m_pCharObj->setState(L"Crouch");
		return true;
	}
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pCharObj->setState(L"Attack1");
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
	m_pCharObj->addState(std::string("Run"), this);
}
bool PlayerRun::Init()
{
	setSprite(L"Kaho", L"Run");
	m_pSprite->setDivideTime(1.8f);
	return true;
}
bool PlayerRun::Frame()
{
	FLOAT fSpeed = m_pCharObj->getSpeed();
	m_CenterPos->y += g_fPerSecFrame * 2.0f;
	if (!m_pCharObj->getLanding())
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Fall");
		return true;
	}

	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Attack1");
		return true;
	}
	if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH || S_Input.GetKey('A') == KEYSTATE::KEY_HOLD)
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Jump");
		return true;
	}
	if ((m_pCharObj->getDir() == 1 && (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD))
		|| (m_pCharObj->getDir() == -1 && (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)))
	{
		FLOAT fSpeed = m_pCharObj->getSpeed();
		m_CenterPos->x += m_pCharObj->getDir() * g_fPerSecFrame * fSpeed;
		*m_rtDraw = m_pSprite->getSpriteRt();
	}
	else if ((S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE) ||
		(S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_FREE))
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Brake");
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
	m_pCharObj->addState(std::string("Brake"), this);
}
bool PlayerBrake::Init()
{
	setSprite(L"Kaho", L"Brake");
	m_pSprite->setDivideTime(0.7f);
	return true;
}
bool PlayerBrake::Frame()
{
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Idle");
		return true;
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerTurn::PlayerTurn(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pCharObj->addState(std::string("Turn"), this);
}
bool PlayerTurn::Init()
{
	setSprite(L"Kaho", L"Turn");
	m_pSprite->setDivideTime(0.3f);
	return true;
}
bool PlayerTurn::Frame()
{
	if (!m_pSprite->Frame())
	{
		m_pCharObj->setDir(-1);
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Run");
		return true;
	}
	if (m_pCharObj->getDir() == 1)
	{
		m_pCharObj->setRendering(INVERSE::LR_ROTATION);
	}
	else
	{
		m_pCharObj->setRendering(INVERSE::DEFAULT);
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerJump::PlayerJump(Player * pPlayer) : PlayerState(pPlayer), m_fJumpSpeed(m_pCharObj->getJumpSpeed()), m_fAcceleration(-3.5f)
{
	m_pCharObj->addState(std::string("Jump"), this);
}
bool PlayerJump::Init()
{
	setSprite(L"Kaho", L"Jump");
	m_pSprite->setDivideTime(1.0f);
	return true;
}
bool PlayerJump::Frame()
{
	m_pCharObj->setLanding(false);
	m_fTimer += g_fPerSecFrame;
	m_fJumpSpeed += m_fAcceleration;

	INT iJumpNumber = m_pCharObj->getJumpNum();
	m_CenterPos->y -= g_fPerSecFrame * m_fJumpSpeed;
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pCharObj->setState(L"AirAttack");
		return true;
	}
	if (m_fJumpSpeed < 0.0f)
	{
		m_pCharObj->setState(L"Fall");
		return true;
	}
	if (iJumpNumber == 0 && (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH))
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Jump2");
		return true;
	}
	FLOAT fSpeed = m_pCharObj->getSpeed();
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

PlayerJump2::PlayerJump2(Player * pPlayer) : PlayerState(pPlayer), m_fJumpSpeed(m_pCharObj->getJumpSpeed(1)), m_fAcceleration(-3.5f)
{
	m_pCharObj->addState(std::string("Jump2"), this);
}
bool PlayerJump2::Init()
{
	setSprite(L"Kaho", L"Jump");
	m_pSprite->setDivideTime(1.0f);
	return true;
}
bool PlayerJump2::Frame()
{
	FLOAT fSpeed = m_pCharObj->getSpeed();
	m_CenterPos->y -= g_fPerSecFrame * m_fJumpSpeed;
	m_fJumpSpeed += m_fAcceleration;

	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pCharObj->setState(L"AirAttack");
		return true;
	}
	if (m_fJumpSpeed < 0.0f)
	{
		m_pCharObj->setState(L"Fall");
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
	m_pCharObj->addState(std::string("Fall"), this);
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
	INT iJumpNum = m_pCharObj->getJumpNum();
	FLOAT fSpeed = m_pCharObj->getSpeed();
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pCharObj->setState(L"AirAttack");
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
		m_pCharObj->setJumpNum(1);
		m_pSprite->setIndex(0);
		m_fTimer = 0.0f;
		m_pCharObj->setState(L"Jump");
		return true;
	}
	if (m_pCharObj->getLanding())
	{
		m_pCharObj->setJumpNum(0);
		m_pSprite->setIndex(0);
		m_fTimer = 0.0f;
		m_pCharObj->setJumpSpeed(220.0f, 170.0f);
		m_pCharObj->setState(L"Rise");
		return true;
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerRise::PlayerRise(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pCharObj->addState(std::string("Rise"), this);
}
bool PlayerRise::Init()
{
	setSprite(L"Kaho", L"Rise");
	m_pSprite->setDivideTime(0.3f);
	return true;
}
bool PlayerRise::Frame()
{
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Idle");
		return true;
	}
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pCharObj->getDir() == -1)		// 방향 같으면
		{
			m_pCharObj->setState(L"Run");
			return true;
		}
	}
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pCharObj->getDir() == 1)
		{
			m_pCharObj->setState(L"Run");
			return true;
		}
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

PlayerCrouch::PlayerCrouch(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pCharObj->addState(std::string("Crouch"), this);
}
bool PlayerCrouch::Init()
{
	setSprite(L"Kaho", L"Crouch");
	m_pSprite->setDivideTime(0.8f);
	return true;
}
bool PlayerCrouch::Frame()
{
	m_CenterPos->y += g_fPerSecFrame * 200.0f;
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(2);
		return true;
	}
	if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_FREE)
	{
		m_pCharObj->setState(L"Rise");
	}
	if (m_pCharObj->getDownable() && S_Input.GetKey('A') == KEYSTATE::KEY_PUSH)
	{
		m_CenterPos->y += 20.0f;
		m_pCharObj->setDownable(false);
		m_pCharObj->setState(L"Fall");
		m_pSprite->setIndex(0);
		return true;
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

PlayerLadderEnter::PlayerLadderEnter(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pCharObj->addState(std::string("LadderEnter"), this);
}
bool PlayerLadderEnter::Init()
{
	setSprite(L"Kaho", L"LadderEnter");
	m_pSprite->setDivideTime(0.8f);
	return true;
}
bool PlayerLadderEnter::Frame()
{
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"LadderDown");
		return true;
	}
	/*if (m_pSprite->getIndex() == 0)
	{
		m_CenterPos->y += 100.0f * g_fPerSecFrame;
	}*/
	m_CenterPos->y += g_fPerSecFrame * 80.0f;
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

PlayerLadderLeave::PlayerLadderLeave(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pCharObj->addState(std::string("LadderLeave"), this);
}
bool PlayerLadderLeave::Init()
{
	setSprite(L"Kaho", L"LadderLeave");
	m_pSprite->setDivideTime(0.8f);
	return true;
}
bool PlayerLadderLeave::Frame()
{
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pCharObj->setState(L"Rise");
		return true;
	}
	m_CenterPos->y -= g_fPerSecFrame * 65.0f;
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

PlayerLadderUp::PlayerLadderUp(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pCharObj->addState(std::string("LadderUp"), this);
}
bool PlayerLadderUp::Init()
{
	setSprite(L"Kaho", L"LadderUp");
	m_pSprite->setDivideTime(1.2f);
	return true;
}
bool PlayerLadderUp::Frame()
{
	if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_HOLD)
	{
		m_pCharObj->setState(L"LadderDown");
		return true;
	}
	if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_UP) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->y -= g_fPerSecFrame * 70.0f;
		if (!m_pSprite->Frame())
		{
			m_pSprite->setIndex(0);
		}
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

PlayerLadderDown::PlayerLadderDown(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pCharObj->addState(std::string("LadderDown"), this);
}
bool PlayerLadderDown::Init()
{
	setSprite(L"Kaho", L"LadderDown");
	m_pSprite->setDivideTime(0.8f);
	return true;
}
bool PlayerLadderDown::Frame()
{
	if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos->y += g_fPerSecFrame * 150.0f;
		if (!m_pSprite->Frame())
		{
			m_pSprite->setIndex(0);
		}
	}
	if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_UP) == KEYSTATE::KEY_HOLD)
	{
		m_pCharObj->setState(L"LadderUp");
		return true;
	}
	//if (!m_pCharObj->isFallState())
	//{
	//	m_pSprite->setIndex(0);
	//	m_pCharObj->setState(L"LadderLeave");
	//	return true;
	//}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

#include "Player.h"
#include "PlayerAttack.h"
#include "PlayerBasicState.h"

float g_fSpeed = 0.0f;

Player::Player()
{ 
	State * state = New PlayerIdle(this);
	state = New PlayerRun(this);
	state = New PlayerBrake(this);
	state = New PlayerTurn(this);
	state = New PlayerAttack(this);
	state = New PlayerAttack2(this);
	state = New PlayerAttack3(this);
	state = New PlayerJump(this);
	state = New PlayerJump2(this);
	state = New PlayerFall(this);
	state = New AirAttack(this);
	state = New PlayerRise(this);
	state = New PlayerCrouch(this);

	state = New PlayerLadderEnter(this);
	state = New PlayerLadderLeave(this);
	state = New PlayerLadderUp(this);
	state = New PlayerLadderDown(this);
	g_fSpeed = m_fSpeed;
}
//bool Player::Init()
//{
//	for (auto it : m_pStateList)
//	{
//		it.second->Init();
//	}
//	g_fSpeed = m_fSpeed;
//	m_pCurrentState = m_pStateList["Fall"];
//	Object::Init();
//	return true;
//}
//bool Player::Frame()
//{
//	m_pCurrentState->Frame();
//
//	Object::Frame();
//	return true;
//}
//bool Player::Render()
//{
//	Object::Render();
//	m_pCurrentState->Render();
//	return true;
//}
//bool Player::Release()
//{
//	for (auto it : m_pStateList)
//	{
//		it.second->Release();
//		delete it.second;
//	}
//	m_pStateList.clear();
//	Object::Release();
//	return true;
//}
//void Player::setState(T_STR szStateName)
//{
//	std::string cstate(szStateName.begin(), szStateName.end());
//	m_pCurrentState = m_pStateList[cstate];
//}

//void Player::setDir(const INT& dir)
//{
//	m_iCurrentDir *= dir;
//}
//INT	Player::getDir()
//{
//	return m_iCurrentDir;
//}

//bool Player::isFallState()
//{
//	auto it = m_pStateList.find("Fall");
//	if (it->second == m_pCurrentState)
//	{
//		return true;
//	}
//	return false;
//}
//void Player::addState(std::string Name, State* state)
//{
//	m_pStateList.insert(std::make_pair(Name, state));
//}
#include "Player.h"
#include "PlayerAttack.h"
#include "PlayerBasicState.h"

CharacterObject::CharacterObject() : m_pCurrentState(nullptr), m_iCurrentDir(1), m_bDownable(false),
									m_iJumpNumber(0), m_fJumpSpeed(200.0f), m_fJumpSpeed2(250.0f), m_bLadder(false),
	m_bDead(false)
{
	m_fSpeed = 250.0f;
}

bool CharacterObject::Init()
{
	for (auto it : m_pStateList)
	{
		it.second->Init();
	}
	m_pCurrentState = m_pStateList["Fall"];
	Object::Init();
	return true;
}
bool CharacterObject::Frame()
{
	m_pCurrentState->Frame();

	Object::Frame();
	return true;
}
bool CharacterObject::Render()
{
	Object::Render();
	m_pCurrentState->Render();
	return true;
}
bool CharacterObject::Release()
{
	for (auto it : m_pStateList)
	{
		it.second->Release();
		delete it.second;
	}
	m_pStateList.clear();
	Object::Release();
	return true;
}

void CharacterObject::setState(T_STR szStateName)
{
	std::string cstate(szStateName.begin(), szStateName.end());
	m_pCurrentState = m_pStateList[cstate];
}
void CharacterObject::setDir(const INT& dir)
{
	m_iCurrentDir *= dir;
}
void CharacterObject::setLadder(const bool& bflag)
{
	m_bLadder = bflag;
}
void CharacterObject::setJumpSpeed(const FLOAT& jSpeed, const FLOAT& jSpeed_2)
{
	m_fJumpSpeed = jSpeed;
	m_fJumpSpeed2 = jSpeed_2;
}
void CharacterObject::setJumpNum(const INT& Num)
{
	m_iJumpNumber = Num;
}
bool CharacterObject::isDead()
{
	return m_bDead;
}
INT	 CharacterObject::getDamage()
{
	return m_Damage;
}
RECT CharacterObject::getEffectObj()
{
	return m_pCurrentState->getEffectRT();
}
std::string	CharacterObject::getCurrentState()
{
	for (auto it : m_pStateList)
	{
		if (it.second == m_pCurrentState)
		{
			return it.first;
		}
	}
	return std::string();
}
void CharacterObject::setDownable(const bool& bdown)
{
	m_bDownable = bdown;
}
void CharacterObject::setHP(const INT& hp)
{
	m_HP -= hp;
	if (m_HP <= 0)
	{
		m_bDead = true;
	}
}
bool CharacterObject::getDownable()
{
	return m_bDownable;
}
INT	CharacterObject::getDir()
{
	return m_iCurrentDir;
}
FLOAT& CharacterObject::getJumpSpeed(const INT& num)
{
	if (num != 0)
	{
		return m_fJumpSpeed2;
	}
	return m_fJumpSpeed;
}
bool CharacterObject::getLadder()
{
	return m_bLadder;
}
bool CharacterObject::isFallState()
{
	auto it = m_pStateList.find("Fall");
	if (it->second == m_pCurrentState)
	{
		return true;
	}
	return false;
}
INT CharacterObject::getJumpNum()
{
	return m_iJumpNumber;
}
void CharacterObject::addState(std::string Name, State* state)
{
	m_pStateList.insert(std::make_pair(Name, state));
}
std::string	CharacterObject::setTransition(E_EVENT Event)
{
	m_sCurrestState = m_fms.StateTransition(m_sCurrestState, Event);
	m_pCurrentState = m_pStateList[m_sCurrestState];
	return m_sCurrestState;
}
#include "Player.h"
#include "PlayerAttack.h"
#include "PlayerBasicState.h"

CharacterObject::CharacterObject() : m_pCurrentState(nullptr), m_iCurrentDir(1)
{
	m_fSpeed = 150.0f;
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
INT	CharacterObject::getDir()
{
	return m_iCurrentDir;
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
void CharacterObject::addState(std::string Name, State* state)
{
	m_pStateList.insert(std::make_pair(Name, state));
}
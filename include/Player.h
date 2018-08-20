#pragma once
#include "CharacterObject.h"



class Player : public CharacterObject
{
public:
	Player();
public:
	void			setJumpNum(const INT&);
public:
	INT				getJumpNum();
private:
	INT				m_iJumpNumber;
};
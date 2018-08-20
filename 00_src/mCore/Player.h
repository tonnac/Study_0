#pragma once
#include "CharacterObject.h"



class Player : public CharacterObject
{
public:
	Player();
public:
	void			setJumpNum	(const INT&);
	void			setDownable	(const bool&);
public:
	INT				getJumpNum	();
	bool			getDownable	();
private:
	INT				m_iJumpNumber;
	bool			m_bDownable;
};
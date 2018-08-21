#pragma once

enum class ENEMYSTATE : unsigned char
{
	MOVE,
	ATTACK
};

enum class ENEMYEVENT : unsigned char
{
	FINDTARGET,
	LOSTTARGET,
	BEATTACKED,
	PATROL
};

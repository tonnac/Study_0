#include "Enemy.h"

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


Enemy::Enemy()
{
}
Enemy::~Enemy()
{

}

bool Enemy::Frame()
{

	return true;
}
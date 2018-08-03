#include <iostream>
#include <memory>

int g_iType = 0; // sun
#define WARRIOR 0
#define MAGICIAN 1


class Attack {};
class Defense {};

class Sword : public Attack {};
class WarriorDefense : public Defense {};

class Magic : public Attack {};
class MagicianDefense : public Defense {};

void Print(Defense * p)
{}


class Character
{
public:
	virtual Attack * CreateAttack() = 0;
	virtual Defense * CreateDefense() = 0;
};
class Magician : public Character
{
public:
	Attack * CreateAttack() { return new Magic; }
	Defense * CreateDefense() { return new MagicianDefense; }
};
class Warrior : public Character
{
public:
	Attack * CreateAttack() { return new Sword; }
	Defense * CreateDefense() { return new WarriorDefense; }
};

int main(void)
{
	g_iType = WARRIOR;
	std::shared_ptr<Character> g_pCharacter;
	if (g_iType == MAGICIAN)
	{
		g_pCharacter = std::make_shared<Magician>();
	}
	else
	{
		g_pCharacter = std::make_shared<Warrior>();
	}
	std::shared_ptr<Attack>pAttack;
	pAttack = std::make_shared<Attack>(g_pCharacter->CreateAttack());

	std::shared_ptr<Defense>a(new Defense);
	std::shared_ptr<Defense>p1 = std::move(a); // a는 비게된다
	

	std::shared_ptr<Defense>pDefense;
	//pDefense = std::move(g_pCharacter->CreateDefense());
	pDefense.reset(g_pCharacter->CreateDefense());
	Print(pDefense.get());

	return 0;
}
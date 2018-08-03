#include <iostream>
#include <list>


class Airplane
{
public:
	virtual void Attack(void) = 0;
};
class FrontAttackAirplane : public Airplane
{
public:
	void Attack(void)
	{
		std::cout << "전방공격" << std::endl;
	}
};
class Decorator : public Airplane
{
public:
	Decorator(Airplane * pObj)
	{
		m_pAirPlane.push_back(pObj);
	}
	void Attack(void)
	{
		std::list<Airplane*>::iterator iter = m_pAirPlane.begin();
		for (; iter != m_pAirPlane.end(); iter++)
		{
			(*iter)->Attack();
		}
	}
	void AddAttack(Airplane * pObj)
	{
		m_pAirPlane.push_back(pObj);
	}
	void DelAttack(Airplane * pObj)
	{
		std::list<Airplane*>::iterator iter;
		iter = std::find(m_pAirPlane.begin(), m_pAirPlane.end(), pObj);
		m_pAirPlane.erase(iter);
	}
protected:
	std::list<Airplane *>m_pAirPlane;
};
class SideAttackAirplane : public Decorator
{
public:
	SideAttackAirplane(Airplane * pAirplane) : Decorator(pAirplane)
	{}
	void Attack(void)
	{
		Decorator::Attack();
		std::cout << "측방공격" << std::endl;
	}
};
class RearAttackAirplane : public Decorator
{
public:
	RearAttackAirplane(Airplane * pAirplane) : Decorator(pAirplane)
	{}
	void Attack(void)
	{
		Decorator::Attack();
		std::cout << "후방공격" << std::endl;
	}
};

class User
{
	Airplane * m_pAttack;
public:
	User() : m_pAttack(nullptr)
	{}
	void SetAttack(Airplane * pAirplane)
	{
		m_pAttack = pAirplane;
	}
	void AddAttack(Airplane * pAirplane)
	{
		Decorator * pAdd = static_cast<Decorator*>(m_pAttack);
		pAdd->AddAttack(pAirplane);
	}
	void DelAttack(Airplane * pAirplane)
	{
		Decorator * pAdd = static_cast<Decorator*>(m_pAttack);
		pAdd->DelAttack(pAirplane);
	}
	void AttackAction()
	{
		m_pAttack->Attack();
	}
	void DeleteAttack()
	{
		if (m_pAttack)
		{
			delete m_pAttack;
			m_pAttack = nullptr;
		}
	}
};



int main(void)
{
	User user;
	Airplane * userFront = new FrontAttackAirplane;
	user.SetAttack(userFront);
	user.AttackAction();
	Airplane * userSide = new SideAttackAirplane(userFront);
	user.SetAttack(userSide);
	user.AddAttack(userFront);
	user.AttackAction();
	Airplane * userRear = new RearAttackAirplane(userSide);
	user.DelAttack(userFront);
	user.SetAttack(userRear);
	user.AttackAction();

	//user.SetAttack(new FrontAttackAirplane);
	//user.AttackAction();
	//user.DeleteAttack();

	//user.SetAttack(new SideAttackAirplane(new FrontAttackAirplane));
	//user.AddAttack(new FrontAttackAirplane);
	//user.DeleteAttack();
	//user.AttackAction();
	//user.DeleteAttack();

	//user.SetAttack(new RearAttackAirplane(new SideAttackAirplane(new FrontAttackAirplane)));
	//user.AttackAction();
	//user.DeleteAttack();

	delete userRear;
	delete userSide;
	delete userFront;

	return 0;
}
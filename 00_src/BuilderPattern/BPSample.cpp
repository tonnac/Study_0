// 객체를 구성하는 부분을 생성하고
// 조합하여 완성한다.
class Product 
{

};
class WarAttack : public Product {};
class WarDefense : public Product {};
class Character 
{
public:
	Product pro[2];
};
class Builder 
{
protected:
	Character * m_pCharacter;
public:
	virtual void BuildAttack() = 0;
	virtual void BuildDefense() = 0;
	virtual Character * GetCharacter(void) = 0;
};
class Warrior : public Builder
{
	Character * GetCharacter(void)
	{
		return m_pCharacter;
	}
};
class Magician : public Builder
{
	Product * a;
	Character * GetCharacter(void)
	{
		return m_pCharacter;
	}
};
class Director 
{
public:
	Character * CreateMaze(Builder & pBuild)
	{
		pBuild.BuildAttack();
		pBuild.BuildDefense();
		return pBuild.GetCharacter();
	};
};

int main(void)
{
	Director director;
	Warrior build;
	director.CreateMaze(build);
	Character * ch = build.GetCharacter();

	return 0;
}
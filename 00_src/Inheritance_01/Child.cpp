#include "Child.h"


Child::~Child()
{
	cout << "Child 소멸자" << endl;
}

void Child::Humanity()
{
	cout << "넘치는 인간미" << endl;
}

void Child::Character()
{
	cout << "불 같은 성품" << endl;
}
void Child::Appearance()
{
	Parent::Appearance();
	cout << "훤칠한 키" << endl;
}
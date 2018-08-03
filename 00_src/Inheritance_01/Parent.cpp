#include "Parent.h"


void Parent::Character()
{
	cout << "차분한 성품" << endl;
}
void Parent::Appearance()
{
	cout << "잘생긴 외모" << endl;
}
void Parent::Wealth()
{
	cout << "재산:" << money << "원" << endl;
}




Parent::~Parent()
{
	cout << "Parent 소멸자" << endl;
}

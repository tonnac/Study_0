#include "Child.h"


Child::~Child()
{
	cout << "Child �Ҹ���" << endl;
}

void Child::Humanity()
{
	cout << "��ġ�� �ΰ���" << endl;
}

void Child::Character()
{
	cout << "�� ���� ��ǰ" << endl;
}
void Child::Appearance()
{
	Parent::Appearance();
	cout << "��ĥ�� Ű" << endl;
}
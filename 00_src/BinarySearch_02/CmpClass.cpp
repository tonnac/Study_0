#include "CmpClass.h"
#include <cstdlib>

std::ostream& operator << (std::ostream & os, const CmpClass& data)
{
	std::cout << "이름: " << data.name << std::endl;
	std::cout << "나이: " << data.age << std::endl;
	std::cout << "번호: " << data.m_iValue<< std::endl << std::endl;
	return os;
}

bool CmpClass::operator > (const CmpClass& src)
{
	if (m_iValue > src.m_iValue) { return true; }

	return false;
}
bool CmpClass::operator < (const CmpClass& src)
{
	if (m_iValue < src.m_iValue) { return true; }

	return false;
}
bool CmpClass::operator == (const CmpClass& src)
{
	if (m_iValue == src.m_iValue) { return true; }

	return false;
}


CmpClass::CmpClass(const int& data) : m_iValue(data)
{
	name[0] = rand() % 26 + 65;
	name[1] = rand() % 26 + 65;
	name[2] = rand() % 26 + 65;
	name[3] = rand() % 26 + 65;
	name[4] = NULL;
	age = rand() % 70;
}
CmpClass::~CmpClass()
{
}

int CmpClass::getValue() const
{
	return m_iValue;
}
int CmpClass::getAge() const
{
	return age;
}
char* CmpClass::getName()
{
	return name;
}
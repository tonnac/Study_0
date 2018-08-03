#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

namespace Pos
{
	enum {TEMPORARY, PERMANENT, CHIEF, DEPARTMENT, PRESIDENT};
}


class TEmployee
{
private:
	char * m_cName;
	const int m_iPos;
	int m_iSalary;
public:
	int GetSalary() const;
	char* GetName() const;
	int GetPos() const;
	virtual void Salaryinput() = 0;
	void inputSalary(const int& money);
	TEmployee(const char * _name, const int& _Pos);
	virtual ~TEmployee();
};


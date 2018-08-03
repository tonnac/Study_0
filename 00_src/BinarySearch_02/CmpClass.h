#pragma once
#include <iostream>

class CmpClass
{
private:
	char name[256];
	int age;
	int m_iValue;
	friend std::ostream& operator << (std::ostream & os, const CmpClass& data);
public:
	int getValue() const;
	int getAge() const;
	char* getName();
	bool operator > (const CmpClass& src);
	bool operator < (const CmpClass& src);
	bool operator == (const CmpClass& src);
	CmpClass(const int& data = 0);
	~CmpClass();
};


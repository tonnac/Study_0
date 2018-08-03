#pragma once
#include <iostream>

using namespace std;

class TEmployeee
{
	enum {TIMEBY,MONTHBY,YEARBY};
public:
	TEmployeee(const char * _name, int _paytype);
	virtual ~TEmployeee();
private:
	char * m_cName;
	int m_iPayType;
};


#pragma once
class CmpClass
{
private:
	int m_iValue;
public:
	bool operator > (const CmpClass& src);
	bool operator < (const CmpClass& src);
	CmpClass(const int& data=0);
	~CmpClass();
};


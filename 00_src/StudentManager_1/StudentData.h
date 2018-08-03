#pragma once
#include <cstring>
#include <iostream>



class StudentData
{
public:
	StudentData(const char * _Name, int _Kor, int _Mat, int _Eng);
	~StudentData();

	static int getiCounter();
	static int getiCurNum();
	int getiNum() const;
	const char* getName() const;

	void setiNum(const int & src);
	static void setCurNum(const int& src);
	void setName(const char* src);
	void setKor(const int& src);
	void setMat(const int& src);
	void setEng(const int& src);

	void DataShow() const;
	StudentData * m_pNext;
private:
	static int s_iCounter;
	static int s_iCurNum;
	char m_cName[20];
	int m_iNum;
	int m_iKor;
	int m_iMat;
	int m_iEng;
	int m_iTotal;
};
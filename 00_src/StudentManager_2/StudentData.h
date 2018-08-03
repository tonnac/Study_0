#pragma once
#include <cstring>
#include <iostream>
#include <ctime>

class DataLinkedList;

class StudentData
{
public:
	StudentData() { m_pNext = nullptr; }
	StudentData(const char * _Name, int _Kor, int _Mat, int _Eng);
	StudentData(const char * _Name, int _Kor, int _Mat, int _Eng, int _Num);
	StudentData(const StudentData & data);
	~StudentData();
	static int getiCounter();
	static int getiCurNum();
	const int getiNum() const;
	const char* getName() const;
	const int getiKor() const;
	const int getiMat() const;
	const int getiEng() const;

	void setiNum(const int & src);
	static void setCurNum(const int& src);
	static void setCounter(const int& src) { s_iCounter = src; }
	void setName(const char* src);
	void setKor(const int& src);
	void setMat(const int& src);
	void setEng(const int& src);

	void DataShow() const;
	void OneShow() const;
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
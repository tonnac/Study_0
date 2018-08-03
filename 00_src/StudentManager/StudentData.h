#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <io.h>
#include <ctime>

class StudentLinkedList;

class StudentData
{
public:
	StudentData(const char * Name,
		const int& Kor, const int &Mat, const int &Eng);
	StudentData(const char * Name,
		const int& Kor, const int &Mat, const int &Eng, const int &Num);
	void setName(const char * srcName);
	void setKor(const int& Kor);
	void setMat(const int& Mat);
	void setEng(const int& Eng);
	void setNum(const int& Num);

	int getNum() const;
	int getKor() const;
	int getMat() const;
	int getEng() const;
	int getTotal() const;
	char* getName() const;


	StudentData * m_pNext;
	void ShowData() const;
	~StudentData();
	static int m_sCounter;
private:
	char * m_cName;
	int m_iNum;
	int m_iKor;
	int m_iMat;
	int m_iEng;
	int m_iTotal;
};


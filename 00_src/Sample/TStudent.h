#pragma once
#include <iostream>
#include <cstdlib>

class TStudent
{
public:
	TStudent();
	~TStudent();
public:
	TStudent operator + (const TStudent& data) const;
	TStudent& operator += (const TStudent& data);
	// 인덱싱 지원
	int operator [](int index);
	// 단항 연산자
	TStudent operator ++ (int n); //후위 증가
	TStudent& operator ++ ();	  // 전위 증가
	TStudent& operator + (const int& iValue);
public:
	void SetSubject(int kor, int eng, int mat);
	int GetTotal();
	void Show();
	void SetTotal(int iValue)
	{
		m_iTotal = iValue;
	}
private:
	int m_iKor; // 0 인덱싱
	int m_iEng; // 1 
	int m_iMat; // 2
	int m_iTotal; // 3
};


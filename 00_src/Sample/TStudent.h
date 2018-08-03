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
	// �ε��� ����
	int operator [](int index);
	// ���� ������
	TStudent operator ++ (int n); //���� ����
	TStudent& operator ++ ();	  // ���� ����
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
	int m_iKor; // 0 �ε���
	int m_iEng; // 1 
	int m_iMat; // 2
	int m_iTotal; // 3
};


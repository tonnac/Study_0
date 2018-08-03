#include "TStudent.h"



TStudent::TStudent()
{
	m_iEng = 0;
	m_iKor = 0;
	m_iMat = 0;
}
TStudent::~TStudent()
{
}

void TStudent::SetSubject(int kor, int eng, int mat)
{
	m_iEng = eng;
	m_iKor = kor;
	m_iMat = mat;

	m_iTotal = m_iEng + m_iKor + m_iMat;
}
int TStudent::GetTotal()
{
	return m_iTotal;
}
void TStudent::Show()
{
	std::cout << "±¹¾î=" << m_iKor << " "
		<< "¿µ¾î=" << m_iEng << " "
		<< "¼öÇÐ=" << m_iMat << " "
		<< "ÃÑÁ¡=" << m_iTotal
		<< std::endl;
}

//¿¬»êÀÚ ÀçÁ¤ÀÇ
//°´Ã¼³¢¸® µ¡¼À
TStudent TStudent:: operator + (const TStudent& data) const
{
	int iTotal = m_iTotal + data.m_iTotal;
	TStudent ret;
	ret.SetSubject(m_iKor + data.m_iKor, m_iEng + data.m_iEng, m_iMat + data.m_iMat);
	return ret;
}
TStudent& TStudent:: operator += (const TStudent& data)
{
	m_iKor += data.m_iKor;
	m_iEng += data.m_iEng;
	m_iMat += data.m_iMat;
	m_iTotal = m_iKor + m_iEng + m_iMat;
	return *this;

	/*int iTotal = m_iTotal + data.m_iTotal;
	TStudent ret;
	ret.SetSubject(m_iKor + data.m_iKor, m_iEng + data.m_iEng, m_iMat + data.m_iMat);
	return ret;*/

	/*return *this + data;*/
}
//ÀÎµ¦½Ì
int TStudent::operator [](int index)
{
	if (index > 3) return -1;
	if (index == 0) return m_iKor;
	if (index == 1) return m_iEng;
	if (index == 2) return m_iMat;
	if (index == 3) return m_iTotal;
	return -1;
}
//´ÜÇ×¿¬»ê
TStudent TStudent::operator ++ (int n)
{
	TStudent iRet = *this;
	m_iTotal += 10;
	return iRet;
}
TStudent& TStudent::operator ++ ()
{
	m_iTotal += 10;
	return *this;
}
//°´Ã¼ + Á¤¼ö
TStudent& TStudent::operator + (const int& iValue)
{
	m_iTotal = m_iTotal + iValue;
	return *this;
}
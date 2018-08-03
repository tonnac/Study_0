#include "StudentData.h"

int StudentData::s_iCounter = 0;
int StudentData::s_iCurNum = 1;

StudentData::StudentData(const char * _Name, int _Kor, int _Mat, int _Eng)
	:m_iKor(_Kor), m_iMat(_Mat), m_iEng(_Eng), m_iTotal(_Kor+_Mat+_Eng)
{
	m_iNum = s_iCurNum++;
	strcpy_s(m_cName, 20, _Name);
	s_iCounter++;
}
StudentData::~StudentData()
{
	s_iCounter--;
}
int StudentData::getiCounter() {return s_iCounter;}
int StudentData::getiCurNum() {return s_iCurNum;}
int StudentData::getiNum() const { return m_iNum; }
const char * StudentData::getName() const{return m_cName;}

void StudentData::DataShow() const
{
	std::cout << m_cName << "\t  " << m_iNum << "\t " << m_iKor <<
		"\t " << m_iMat << "\t " << m_iEng << "\t " << m_iTotal << std::endl;
}

void StudentData::setiNum(const int &src) { m_iNum = src; }
void StudentData::setCurNum(const int& src) { s_iCurNum = src; }
void StudentData::setName(const char* src)
{
	strcpy_s(m_cName, 20, src);
}
void StudentData::setKor(const int& src) 
{
	m_iKor = src;
	m_iTotal = m_iKor + m_iEng + m_iMat;
}
void StudentData::setMat(const int& src) 
{ 
	m_iMat = src; 
	m_iTotal = m_iKor + m_iEng + m_iMat;
}
void StudentData::setEng(const int& src) 
{ 
	m_iEng = src; 
	m_iTotal = m_iKor + m_iEng + m_iMat;
}
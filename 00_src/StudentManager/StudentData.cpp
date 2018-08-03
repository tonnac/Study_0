#include "StudentData.h"
int StudentData::m_sCounter = 1;

StudentData::StudentData(const char * Name,
	const int& Kor, const int &Mat, const int &Eng)
	:m_pNext(nullptr), m_iNum(m_sCounter),
	m_iKor(Kor), m_iMat(Mat), m_iEng(Eng), m_iTotal(Kor + Mat + Eng)
{
	m_cName = new char[strlen(Name) + 1];
	strcpy_s(m_cName, strlen(Name) + 1, Name);
	m_sCounter++;
}
StudentData::StudentData(const char * Name,
	const int& Kor, const int &Mat, const int &Eng,const int &Num)
	:m_pNext(nullptr), m_iNum(Num),
	m_iKor(Kor), m_iMat(Mat), m_iEng(Eng), m_iTotal(Kor + Mat + Eng)
{
	m_cName = new char[strlen(Name) + 1];
	strcpy_s(m_cName, strlen(Name) + 1, Name);
	m_sCounter++;
}
void StudentData::setName(const char * srcName)
{
	if (m_cName)
		delete[] m_cName;
	m_cName = new char[strlen(srcName) + 1];
	strcpy_s(m_cName, strlen(srcName) + 1, srcName);
}
void StudentData::setKor(const int& Kor)
{
	m_iKor = Kor;
	m_iTotal = m_iKor + m_iMat + m_iEng;
}
void StudentData::setMat(const int& Mat)
{
	m_iMat = Mat;
	m_iTotal = m_iKor + m_iMat + m_iEng;
}
void StudentData::setEng(const int& Eng)
{
	m_iEng = Eng;
	m_iTotal = m_iKor + m_iMat + m_iEng;
}
void StudentData::setNum(const int& Num)
{
	m_iNum = Num;
}
int StudentData::getNum() const
{
	return m_iNum;
}
int StudentData::getKor() const
{
	return m_iKor;
}
int StudentData::getMat() const
{
	return m_iMat;
}
int StudentData::getEng() const
{
	return m_iEng;
}
int StudentData::getTotal() const
{
	return m_iTotal;
}
char* StudentData::getName() const
{
	return m_cName;
}
void StudentData::ShowData() const
{
	std::cout << m_cName << "\t  " << m_iNum << "\t " << m_iKor << "\t "
		<< m_iMat << "\t " << m_iEng << "\t " << m_iTotal << std::endl;
}

StudentData::~StudentData()
{
	delete[] m_cName;
	m_sCounter--;
}

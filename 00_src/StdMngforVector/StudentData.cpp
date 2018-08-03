#include "StudentData.h"

int StudentData::s_iCounter = 0;
int StudentData::s_iCurNum = 1;

StudentData::StudentData(const char * _Name, int _Kor, int _Mat, int _Eng)
	:m_iKor(_Kor), m_iMat(_Mat), m_iEng(_Eng), m_iTotal(_Kor+_Mat+_Eng), m_iType(0)
{
	m_iNum = s_iCurNum++;
	strcpy_s(m_cName, 20, _Name);
	s_iCounter++;
}
StudentData::StudentData(const char * _Name, int _Kor, int _Mat, int _Eng, int _Num)
	:m_iKor(_Kor), m_iMat(_Mat), m_iEng(_Eng), m_iTotal(_Kor + _Mat + _Eng), m_iNum(_Num), m_iType(0)
{
	s_iCurNum++;
	strcpy_s(m_cName, 20, _Name);
	s_iCounter++;
}
StudentData::StudentData(const StudentData & data) : m_iNum(data.m_iNum) ,m_iKor(data.m_iKor),
m_iMat(data.m_iMat), m_iEng(data.m_iEng), m_iTotal(data.m_iTotal), m_iType(data.m_iType)
{
	strcpy_s(m_cName, 20, data.m_cName);
}
StudentData::StudentData(StudentData&& Data)
{
	strcpy_s(m_cName, 20, Data.m_cName);
	m_iNum = Data.m_iNum;
	m_iKor = Data.m_iKor;
	m_iMat = Data.m_iMat;
	m_iEng = Data.m_iEng;
	m_iTotal = Data.m_iTotal;
	Data.m_iNum = 0;
	Data.m_iKor = 0;
	Data.m_iMat = 0;
	Data.m_iEng = 0;
	Data.m_iTotal = 0;
}
StudentData::StudentData(const char * src) : m_iType(1)
{
	strcpy_s(m_cName, 20, src);
	s_iCounter++;
}
StudentData::StudentData(const int & Value) : m_iNum(Value), m_iType(0)
{
	s_iCounter++;
}
StudentData::~StudentData()
{
	s_iCounter--;
}

int StudentData::getiCounter() {return s_iCounter;}
int StudentData::getiCurNum() {return s_iCurNum;}
const int StudentData::getiNum() const { return m_iNum; }
const int StudentData::getiKor() const { return m_iKor; }
const int StudentData::getiMat() const { return m_iMat; }
const int StudentData::getiEng() const { return m_iEng; }
const char * StudentData::getName() const {return m_cName;}

void StudentData::DataShow() const
{
	std::cout << m_cName << "\t " << m_iNum << "\t " << m_iKor <<
		"\t " << m_iMat << "\t " << m_iEng << "\t " << m_iTotal << std::endl;
}

void StudentData::OneShow() const
{
	std::cout << "============================================" << std::endl;
	std::cout << "이름\t" << "번호\t" << "국어\t" << "수학\t" << "영어\t"
		<< "총점" << std::endl;
	DataShow();
	std::cout << "============================================" << std::endl;
}

void StudentData::setiNum(const int &src) { m_iNum = src; }
void StudentData::setCurNum(const int& src) { s_iCurNum = src; }
void StudentData::setName(const char* src) { strcpy_s(m_cName, 20, src); }
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

bool StudentData::operator()(const StudentData* src)
{
	if (m_iType)
	{
		return !_stricmp(src->m_cName, m_cName);
	}
	else
	{
		return m_iNum == src->m_iNum;
	}
}
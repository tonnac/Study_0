#include "StudentData.h"
#include "DataLinkedList.h"

using namespace std;

std::istream& operator>>(std::istream&is, DataLinkedList::EDIT & type)
{
	int num;
	is >> num;
	type = static_cast<DataLinkedList::EDIT>(num);
	return is;
}

DataLinkedList::DataLinkedList()
{}
DataLinkedList::~DataLinkedList()
{
	std::list<StudentData*>::iterator iter;
	for (iter = DataList.begin(); iter != DataList.end(); iter++)
	{
		delete *iter;
	}
}
void DataLinkedList::AddLink(StudentData * src)
{
	DataList.push_back(src);
}
//void DataLinkedList::LoadLink(StudentData * src)
//{
//	if (m_pHead == nullptr)
//	{
//		m_pHead = new StudentData(*src);
//		m_pHead->m_pNext = nullptr;
//		m_pTail = m_pHead;
//	}
//	else
//	{
//		m_pTail->m_pNext = new StudentData(*src);
//		m_pTail = m_pTail->m_pNext;
//		m_pTail->m_pNext = nullptr;
//		Sort();
//	}
//}
void DataLinkedList::DelLink(std::list<StudentData*>::iterator iter)
{
	delete *iter;
	DataList.erase(iter);
}
void DataLinkedList::EditLink(std::list<StudentData*>::iterator iter)
{
	while (1)
	{
		EDIT iSelect = EDIT::ENG;
		std::cout << "1. 이름" << std::endl;
		std::cout << "2. 국어점수" << std::endl;
		std::cout << "3. 수학점수" << std::endl;
		std::cout << "4. 영어점수" << std::endl;
		std::cout << "5. 나가기" << std::endl;
		std::cout << "수정할 데이터를 고르세요: ";
		std::cin >> iSelect;
		switch (iSelect)
		{
		case EDIT::NAME:
			EditName(**iter);
			(*iter)->OneShow();
			break;
		case EDIT::KOR:
			EditKor(**iter);
			(*iter)->OneShow();
			break;
		case EDIT::MAT:
			EditMat(**iter);
			(*iter)->OneShow();
			break;
		case EDIT::ENG:
			EditEng(**iter);
			(*iter)->OneShow();
			break;
		case EDIT::UPPER:
			system("cls");
			return;
		default:
			system("cls");
			std::cout << "잘못된 입력입니다." << std::endl;
		}
	}
}
std::list<StudentData*>::iterator DataLinkedList::getBegin()
{
	std::list<StudentData*>::iterator iter = DataList.begin();
	return iter;
}
std::list<StudentData*>::iterator DataLinkedList::getEnd()
{
	std::list<StudentData*>::iterator iter = DataList.end();
	return iter;
}
std::list<StudentData*>::iterator DataLinkedList::SearchByName(const char * src)
{
	std::list<StudentData*>::iterator iter;
	iter = find_if(DataList.begin(), DataList.end(), StudentData(src));
	return iter;
}
std::list<StudentData*>::iterator DataLinkedList::SearchByNum(const int& src)
{
	std::list<StudentData*>::iterator iter;
	iter = find_if(DataList.begin(), DataList.end(), StudentData(src));
	return iter;
}
void DataLinkedList::PrintAllData()
{
	std::list<StudentData*>::iterator iter = DataList.begin();
	std::list<StudentData*>::iterator siter = DataList.begin();
	std::cout << "============================================" << std::endl;
	std::cout << "이름\t" << "번호\t" << "국어\t" << "수학\t" << "영어\t"
		<< "총점" << std::endl;
	for (; iter!=DataList.end(); iter++)
	{
		(*iter)->DataShow();
	}
	std::cout << "============================================" << std::endl;
}
void DataLinkedList::EditName(StudentData & src) const
{
	char srcName[256];
	std::cout << "이름 입력: ";
	std::cin >> srcName;
	src.setName(srcName);
	system("cls");
	std::cout << "이름 수정이 완료되었습니다." << std::endl;
}
void DataLinkedList::EditKor(StudentData & src) const
{
	int Kor;
	std::cout << "국어점수 입력: ";
	std::cin >> Kor;
	src.setKor(Kor);
	system("cls");
	std::cout << "국어점수 수정이 완료되었습니다." << std::endl;
}
void DataLinkedList::EditMat(StudentData & src) const
{
	int Mat;
	std::cout << "수학점수 입력: ";
	std::cin >> Mat;
	src.setMat(Mat);
	system("cls");
	std::cout << "수학점수 수정이 완료되었습니다." << std::endl;
}
void DataLinkedList::EditEng(StudentData & src) const
{
	int Eng;
	std::cout << "영어점수 입력: ";
	std::cin >> Eng;
	src.setEng(Eng);
	system("cls");
	std::cout << "영어점수 수정이 완료되었습니다." << std::endl;
}
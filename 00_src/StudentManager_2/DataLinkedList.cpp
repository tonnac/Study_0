#include "StudentData.h"
#include "DataLinkedList.h"

std::istream& operator>>(std::istream&is, DataLinkedList::EDIT & type)
{
	int num;
	is >> num;
	type = static_cast<DataLinkedList::EDIT>(num);
	return is;
}

DataLinkedList::DataLinkedList() : m_pHead(nullptr), m_pTail(nullptr)
{}
DataLinkedList::~DataLinkedList()
{
	StudentData * temp = m_pHead;
	StudentData * temp1 = temp;
	while (temp != nullptr)
	{
		temp1 = temp->m_pNext;
		delete temp;
		temp = temp1;
	}
	m_pHead = nullptr;
}
void DataLinkedList::AddLink(StudentData * src)
{
	if (m_pHead == nullptr)
	{
		m_pHead = src;
		m_pTail = m_pHead;
	}
	else
	{
		m_pTail->m_pNext = src;
		Sort();
	}
}
void DataLinkedList::LoadLink(StudentData * src)
{
	if (m_pHead == nullptr)
	{
		m_pHead = new StudentData(*src);
		m_pHead->m_pNext = nullptr;
		m_pTail = m_pHead;
	}
	else
	{
		m_pTail->m_pNext = new StudentData(*src);
		m_pTail = m_pTail->m_pNext;
		m_pTail->m_pNext = nullptr;
		Sort();
	}
}
void DataLinkedList::DelLink(StudentData * src)
{
	int DelNodeNum;
	if (src == m_pHead)
	{
		DelNodeNum = src->getiNum();
		m_pHead = m_pHead->m_pNext;
		delete src;
	}
	else
	{	
		StudentData * temp = m_pHead->m_pNext;
		StudentData * temp1 = m_pHead;
		while (temp != nullptr)
		{
			if (temp == src)
			{
				DelNodeNum = temp->getiNum();
				temp1->m_pNext = temp->m_pNext;
				delete temp;
				break;
			}
			temp = temp->m_pNext;
			temp1 = temp1->m_pNext;
		}
	}
	if (DelNodeNum < StudentData::getiCurNum())
	{
		StudentData::setCurNum(DelNodeNum);
	}
}
void DataLinkedList::EditLink(StudentData * src)
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
			EditName(*src);
			src->OneShow();
			break;
		case EDIT::KOR:
			EditKor(*src);
			src->OneShow();
			break;
		case EDIT::MAT:
			EditMat(*src);
			src->OneShow();
			break;
		case EDIT::ENG:
			EditEng(*src);
			src->OneShow();
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
StudentData* DataLinkedList::SearchByName(const char * src) const
{
	StudentData * temp = m_pHead;
	while (temp != nullptr)
	{
		const char * tempName = temp->getName();
		if (!_stricmp(tempName, src))
		{
			return temp;
		}
		temp = temp->m_pNext;
	}
	return nullptr;
}
StudentData* DataLinkedList::SearchByNum(const int& src) const
{
	StudentData * temp = m_pHead;	
	while (temp != nullptr)
	{
		int tempNum = temp->getiNum();
		if (tempNum == src)
		{
			return temp;
		}
		temp = temp->m_pNext;
	}
	return nullptr;
}
StudentData* DataLinkedList::GetHead()const { return m_pHead; }
void DataLinkedList::PrintAllData() const
{
	StudentData * temp = m_pHead;
	std::cout << "============================================" << std::endl;
	std::cout << "이름\t" << "번호\t" << "국어\t" << "수학\t" << "영어\t"
		<< "총점" << std::endl;
	for (int i = 0; i < StudentData::getiCounter(); i++)
	{
		if (!(i % 26) && i!=0)
		{
			std::cout << "============================================" << std::endl;
			std::cout << "이름\t" << "번호\t" << "국어\t" << "수학\t" << "영어\t"
				<< "총점" << std::endl;
		}
		temp->DataShow();
		temp = temp->m_pNext;
	}
	std::cout << "============================================" << std::endl;
}
void DataLinkedList::Sort()
{
	for (int i = 0; i < StudentData::getiCounter(); i++)
	{
		StudentData * temp = m_pHead;
		while (temp->m_pNext->m_pNext != nullptr)
		{
			if (temp->m_pNext->getiNum() > temp->m_pNext->m_pNext->getiNum())
			{
				StudentData * temp1 = temp->m_pNext;
				StudentData * temp2 = temp->m_pNext->m_pNext;
				temp->m_pNext = temp2;
				temp1->m_pNext = temp2->m_pNext;
				temp2->m_pNext = temp1;
			}
			temp = temp->m_pNext;
		}
		m_pTail = temp->m_pNext;
	}
	if (m_pHead->getiNum() > m_pHead->m_pNext->getiNum())
	{
		StudentData * temp1 = m_pHead->m_pNext;
		m_pHead->m_pNext = temp1->m_pNext;
		temp1->m_pNext = m_pHead;
		m_pHead = temp1;
	}
	StudentData * temp = m_pHead;
	int tempNum = temp->getiNum();
	for (int i = 0; i < StudentData::getiCounter(); i++)
	{
		temp = temp->m_pNext;
		if (temp == nullptr || (tempNum = temp->getiNum()) != i + 2)
		{
			StudentData::setCurNum(i + 2);
			break;
		}
	}
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
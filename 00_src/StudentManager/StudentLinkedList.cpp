#include "StudentLinkedList.h"
#include <iostream>

using namespace std;

StudentLinkedList::StudentLinkedList() : m_pHead(nullptr), m_pTail(nullptr)
{}
void StudentLinkedList::AddLink(StudentData * src)
{
	if (m_pHead == nullptr)
	{
		m_pHead = src;
		m_pTail = m_pHead;
		return;
	}
	m_pTail->m_pNext = src;
	m_pTail = m_pTail->m_pNext;
}
void StudentLinkedList::DelLink(StudentData * src)
{
	StudentData * temp = m_pHead;
	StudentData * temp1 = temp;
	if (src == m_pHead)
	{
		m_pHead = m_pHead->m_pNext;
		delete temp;
	}
	else
	{
		while (temp != nullptr)
		{
			if (temp == src)
			{
				temp1->m_pNext = temp->m_pNext;
				delete temp;
				break;
			}
			temp1 = temp;
			temp = temp->m_pNext;
		}
	}
	temp = m_pHead;
	for (int i = 1; i < StudentData::m_sCounter; i++)
	{
		temp->setNum(i);
		temp = temp->m_pNext;
	}
}
void StudentLinkedList::EditLink(StudentData * src)
{
	char name[256];
	int Kor;
	int Mat;
	int Eng;
	cout << "�̸� �Է�: ";
	cin >> name;
	cout << "�������� �Է�: ";
	cin >> Kor;
	cout << "�������� �Է�: ";
	cin >> Mat;
	cout << "�������� �Է�: ";
	cin >> Eng;
	src->setName(name);
	src->setKor(Kor);
	src->setMat(Mat);
	src->setEng(Eng);
}
StudentData* StudentLinkedList::SearchByNumber(const int& num)
{
	if (m_pHead == nullptr)
	{
		return nullptr;
	}
	StudentData * temp = m_pHead;
	int tempNum = temp->getNum();
	while (temp!=nullptr)
	{	
		tempNum = temp->getNum();
		if (tempNum == num)
		{
			return temp;
		}
		temp = temp->m_pNext;
	}
	return nullptr;
}
StudentData* StudentLinkedList::SearchByName(const char * src)
{
	if (m_pHead == nullptr)
	{
		return nullptr;
	}
	StudentData * temp = m_pHead;
	char * tempName = temp->getName();
	while (temp != nullptr)
	{
		tempName = temp->getName();
		if (!_stricmp(tempName,src))
		{
			return temp;
		}
		temp = temp->m_pNext;
	}
	return nullptr;
}
StudentData* StudentLinkedList::getHead() const
{
	return m_pHead;
}
StudentLinkedList::~StudentLinkedList()
{
	int i = 0;
	StudentData * temp = m_pHead;
	StudentData * temp1 = m_pHead;
	while (temp1 != nullptr)
	{
		temp1 = temp1->m_pNext;
		temp->m_pNext = nullptr;
		delete temp;
		temp = temp1;
	}
	m_pHead = nullptr;
}
#include "LLLinked.h"
#include <iostream>

LList* LLLinked::AscSearchNode(LList * end, LList * NewNode) //Ascending
{
	if (NewNode->m_iValue > end->m_iValue || end == m_pHead)
	{
		return end;
	}
	return AscSearchNode(end->m_pPrev, NewNode);
}
LList* LLLinked::DesSearchNode(LList * end, LList * NewNode) //Descending
{
	if (NewNode->m_iValue < end->m_iValue || end == m_pHead)
	{
		return end;
	}
	return DesSearchNode(end->m_pPrev, NewNode);
}
void LLLinked::Show() const
{
	LList * temp = m_pHead->m_pNext;
	while (temp != m_pTail)
	{
		std::cout << temp->m_iValue << " ";
		temp = temp->m_pNext;
	}
}

void LLLinked::Sortrule(FP fp)
{
	ad = fp;
}

void LLLinked::push(const int & iValue)
{
	LList * NewList = new LList(iValue);
	LList * temp = (this->*ad)(m_pTail->m_pPrev, NewList);
	NewList->m_pNext = temp->m_pNext;
	temp->m_pNext->m_pPrev = NewList;
	temp->m_pNext = NewList;
	NewList->m_pPrev = temp;
}
void LLLinked::push(LList& src)
{
	LList * temp = (this->*ad)(m_pTail->m_pPrev, &src);
	src.m_pNext = temp->m_pNext;
	temp->m_pNext->m_pPrev = &src;
	temp->m_pNext = &src;
	src.m_pPrev = temp;
}

LLLinked::LLLinked()
{
	m_pHead = new LList;
	m_pTail = new LList;
	m_pHead->m_pNext = m_pTail;
	m_pTail->m_pPrev = m_pHead;
}
LLLinked::~LLLinked()
{
	LList * temp = m_pHead;
	while (m_pHead != nullptr)
	{
		m_pHead = m_pHead->m_pNext;
		delete temp;
		temp = m_pHead;
	}
	m_pTail = nullptr;
}


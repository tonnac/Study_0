#pragma once
#include "StudentData.h"

class StudentLinkedList
{
public:
	StudentLinkedList();
	void AddLink(StudentData * src);
	void DelLink(StudentData * src);
	void EditLink(StudentData * src);
	StudentData* SearchByNumber(const int& num);
	StudentData* SearchByName(const char * src);
	StudentData* getHead() const;
	~StudentLinkedList();
private:
	StudentData * m_pHead;
	StudentData * m_pTail;
};
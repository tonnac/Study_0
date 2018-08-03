#pragma once
#include "StudentData.h"


class DataLinkedList
{
public:
	enum class EDIT {NAME=1,KOR,MAT,ENG,UPPER};
	DataLinkedList();
	~DataLinkedList();
	void AddLink(StudentData * src);
	void LoadLink(StudentData * src);
	void DelLink(StudentData * src);
	void EditLink(StudentData * src);
	StudentData* GetHead() const;
	StudentData* SearchByName(const char * src) const;
	StudentData* SearchByNum(const int& src) const;
	void PrintAllData() const;
private:
	friend std::istream& operator>>(std::istream&os, EDIT& type);
	void Sort();
	void EditName(StudentData & src) const;
	void EditKor(StudentData & src) const;
	void EditMat(StudentData & src) const;
	void EditEng(StudentData & src) const;
	StudentData * m_pHead;
	StudentData * m_pTail;
};


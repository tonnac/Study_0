#pragma once
#include "StudentData.h"
#include <list>
#include <algorithm>


class DataLinkedList
{
public:
	enum class EDIT {NAME=1,KOR,MAT,ENG,UPPER};
	DataLinkedList();
	~DataLinkedList();
	void AddLink(StudentData * src);
	//void LoadLink(StudentData * src);
	void DelLink(std::list<StudentData*>::iterator iter);
	void EditLink(std::list<StudentData*>::iterator iter);
	std::list<StudentData*>::iterator getBegin();
	std::list<StudentData*>::iterator getEnd();
	std::list<StudentData*>::iterator SearchByName(const char * src);
	std::list<StudentData*>::iterator SearchByNum(const int& src);
	void PrintAllData();
private:
	friend std::istream& operator>>(std::istream&os, EDIT& type);
	void EditName(StudentData & src) const;
	void EditKor(StudentData & src) const;
	void EditMat(StudentData & src) const;
	void EditEng(StudentData & src) const;
	std::list<StudentData*> DataList;
};


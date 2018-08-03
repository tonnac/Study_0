#pragma once
#include "StudentData.h"
#include <vector>
#include <algorithm>


class DataLinkedList
{
public:
	enum class EDIT {NAME=1,KOR,MAT,ENG,UPPER};
	DataLinkedList();
	~DataLinkedList();
	void AddLink(StudentData * src);
	//void LoadLink(StudentData * src);
	void DelLink(std::vector<StudentData*>::iterator iter);
	void EditLink(std::vector<StudentData*>::iterator iter);
	std::vector<StudentData*>::iterator getBegin();
	std::vector<StudentData*>::iterator getEnd();
	std::vector<StudentData*>::iterator SearchByName(const char * src);
	std::vector<StudentData*>::iterator SearchByNum(const int& src);
	void PrintAllData();
private:
	friend std::istream& operator>>(std::istream&os, EDIT& type);
	void EditName(StudentData & src) const;
	void EditKor(StudentData & src) const;
	void EditMat(StudentData & src) const;
	void EditEng(StudentData & src) const;
	std::vector<StudentData*> DataList;
};


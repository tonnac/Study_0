#pragma once
#include "DataLinkedList.h"
class StdHandler
{
public:
	enum MENU { ADD = 1, SEARCH, EDIT, DELETE, PRINT, RANDOM, SAVE, LOAD, EXIT };
	void MainMenu();
	void AddStudent();
	void EditStudent();
	void DeleteStudent();
	void SearchStudent();
	void PrintStudent();
	void RandomCreate();
	void SaveFile();
	void LoadFile();
private:
	friend std::istream& operator>>(std::istream&is, MENU& type);
	DataLinkedList m_dList;
};


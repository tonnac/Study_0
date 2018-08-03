#pragma once
#include "FileIO.h"

class StudentHandler
{
public:
	enum class MENU { ADD = 1, EDIT, SEARCH, DELETE, PRINT, RANDOM, SAVE, LOAD, EXIT };
	void MainMenu();
	void AddStudent();
	void SearchStudent();
	void EditStudent();
	void DeleteStudent();
	void PrintStudent();
	void RandomCreate();
	void SaveFile();
	void LoadFile();
private:
	StudentLinkedList StdList;
	FileIO m_fIO;
};
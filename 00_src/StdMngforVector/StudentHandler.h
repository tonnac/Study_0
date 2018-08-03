#pragma once
#include "FileIO.h"
class StudentHandler
{
public:
	enum class MENU { ADD = 1, SEARCH, EDIT, DELETE, PRINT, RANDOM, SAVE, LOAD, EXIT };
	enum class SELECT { NAME = 1, NUMBER = 2 };
	void MainMenu();
	void AddData();
	void SearchData(const int & type);
	void EditData();
	void DeleteData();
	void PrintData();
	void RandomInput();
	void SaveFile();
	void LoadFile();
private:
	void SearchName(const int & type);
	void SearchNumber(const int & type);
	friend std::istream& operator >> (std::istream&is, MENU& type);
	friend std::istream& operator >> (std::istream&is, SELECT& type);
	DataLinkedList m_dStd;
	FileIO m_fIO;
};


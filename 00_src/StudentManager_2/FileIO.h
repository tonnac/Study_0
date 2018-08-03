#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "DataLinkedList.h"
#include <io.h>
#include <stdio.h>

class FileIO
{
public:
	FileIO() : MAXNUM(15), iFileNum(0)
	{
		m_file = new _finddata_t[MAXNUM];
	}
	~FileIO()
	{
		delete[] m_file;
	}
	void FileSave(const DataLinkedList& src);
	void FileLoad(const char * pFilename, int n, DataLinkedList& src);
	int FileCheck(const char * pFilename);
	void FindFile(void);
	void FileSort(struct _finddata_t * pFile);
	void prinfFile(void);
	int Binarytextsave(void);
	int Binarytextload(char* pFilename);
	char* Datafileload(void);
private:
	struct _finddata_t * m_file;
	int iFileNum;
	const int MAXNUM;
};





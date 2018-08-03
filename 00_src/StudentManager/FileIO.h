#pragma once
#include"StudentLinkedList.h"



class FileIO
{
public:
	FileIO();
	void FileSave(const StudentLinkedList& src);
	void FileLoad(const char * pFilename, int n, StudentLinkedList* src);
	void FindFile(void);
	void FileSort(struct _finddata_t * pFile);
	void prinfFile(void);
	int Binarytextload(char* pFilename);
	char* Datafileload(void);
	~FileIO();
private:
	struct _finddata_t * g_file;
	static int iFileNum;
	static const int MaxCount = 15;
};


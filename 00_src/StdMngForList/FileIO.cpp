#include "FileIO.h"

void FileIO::FileSave (DataLinkedList& src)
{
	FILE * fp;
	int Mode;
	int Binary = 0;
	time_t now = time(NULL);
	struct tm * lt = localtime(&now);
	char output[256];
	strftime(output, 256, "%y년%m월%d일%H시%M분%S초", lt);
	strcat(output, ".txt");	
	Mode = Binarytextsave();
	if (Mode)
	{
		if (FileCheck(output))
		{
			fp = fopen(output, "wt");
			if (fp == NULL)
			{
				system("cls");
				puts("파일 불러오기 실패.");
				return;
			}
			std::list<StudentData*>::iterator iter = src.getBegin();
			fprintf(fp, "1\n");
			fprintf(fp, "%d %d", StudentData::getiCounter(), StudentData::getiCurNum());
			for (; iter!=src.getEnd(); iter++)
			{
				fprintf(fp, "\n%d %s %d %d %d %d", (*iter)->getiNum(),
					(*iter)->getName(),
					(*iter)->getiKor(),
					(*iter)->getiMat(),
					(*iter)->getiEng(),
					(*iter)->getiKor() + (*iter)->getiMat() + (*iter)->getiEng());
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		if (FileCheck(output))
		{
			fp = fopen(output, "wb");
			if (fp == NULL)
			{
				system("cls");
				puts("파일 불러오기 실패.");
				return;
			}
			int Cnt = StudentData::getiCounter();
			int CurNum = StudentData::getiCurNum();
			std::list<StudentData*>::iterator iter = src.getBegin();
			fprintf(fp, "%d",Binary);
			fwrite((void*)&Cnt, sizeof(int), 1, fp);
			fwrite((void*)&CurNum, sizeof(int), 1, fp);
			for (; iter != src.getEnd(); iter++)
			{
				fwrite((void*)*iter, sizeof(StudentData), 1, fp);
			}
		}
		else
		{
			return;
		}

	}
	system("cls");
	printf("%s 파일에 저장되었습니다.\n", output);
	fclose(fp);
}
void FileIO::FileLoad(const char * pFilename, int n, DataLinkedList& src)
{
	int Binary;
	FILE * fp;
	if (n)
	{
		fp = fopen(pFilename, "rt");
		if (fp == NULL)
		{
			system("cls");
			puts("파일 불러오기 실패.");
			return;
		}
		int Cnt;
		int iCurNum;
		fscanf(fp, "%d\n", &Binary);
		fscanf(fp, "%d %d", &Cnt, &iCurNum);
		std::list<StudentData*>::iterator iter = src.getBegin();
		//if (*iter)
		//{
		//	for (; iter != src.getEnd(); iter++)
		//	{
		//		src.DelLink(**iter);
		//	}
		//}
		char cName[256];
		int iNum;
		int iKor;
		int iMat;
		int iEng;
		int iTotal;
		for (int iCnt = 0; iCnt < Cnt; iCnt++)
		{
			fscanf(fp, "%d %s %d %d %d %d",
				&iNum,
				cName,
				&iKor,
				&iMat,
				&iEng,
				&iTotal);
			src.AddLink(new StudentData(cName, iKor, iMat, iEng,iNum));
		}
		if (Cnt > 0)
		{
			StudentData::setCounter(Cnt);
		}
		StudentData::setCurNum(iCurNum);

	}
	else
	{
		fp = fopen(pFilename, "rb");
		if (fp == NULL)
		{
			system("cls");
			puts("파일 불러오기 실패.");
			return;
		}
		int Cnt;
		int iCurNum;
		fscanf(fp, "%d", &Binary);
		fread((void*)&Cnt, sizeof(int), 1, fp);
		fread((void*)&iCurNum, sizeof(int), 1, fp);



		//if (src.GetHead() != nullptr)
		//{
		//	src.~DataLinkedList();
		//}
		StudentData ** temp = new StudentData*[Cnt];
		for (int i = 0; i < Cnt; i++)
		{
			temp[i] = new StudentData;
		}
		for (int i = 0; i < Cnt; i++)
		{
			fread((void*)temp[i], sizeof(StudentData), 1, fp);
			src.AddLink(temp[i]);
		}
		delete temp;
		if (Cnt > 0)
		{
			StudentData::setCounter(Cnt);
		}
		StudentData::setCurNum(iCurNum);
	}
	fclose(fp);
	system("cls");
	printf("%s 파일을 불러왔습니다.\n", pFilename);
}
int  FileIO::FileCheck(const char * pFilename)
{
	FILE * Load = fopen(pFilename, "r");
	if (Load == NULL)
	{
		return 1;
	}
	long eof;
	long sof;
	fseek(Load, 0, SEEK_CUR);
	sof = ftell(Load);
	fseek(Load, 0, SEEK_END);
	eof = ftell(Load);
	if (sof != eof)
	{
		printf("파일에 데이터가 이미 존재합니다. 덮어쓰시겠습니까(Y/N): ");
		switch (getchar())
		{
		case 89:
		case 121:
			fclose(Load);
			return 1;
		case 78:
		case 110:
			system("cls");
			fclose(Load);
			return 0;
		default:
			system("cls");
			puts("잘못된 입력입니다.\n\n");
			fclose(Load);
			return 0;
		}
	}
	else
	{
		fclose(Load);
		return 1;
	}
}
void FileIO::FindFile(void)
{
	struct _finddata_t file;
	intptr_t hFile = _findfirst("*.txt", &file);

	if (hFile == -1L)
	{
		return;
	}

	do
	{
		FileSort(&file);
	} while (_findnext(hFile, &file) == 0);
}
void FileIO::FileSort(struct _finddata_t * File)
{
	struct _finddata_t temp;
	if (iFileNum >= MAXNUM)
	{
		return;
	}
	
	for (int i = 0; i < iFileNum; i++)							      // Mem to mem
	{
		memcpy(&temp, &m_file[i], sizeof(struct _finddata_t));
		if (File->time_create > temp.time_create)
		{
			for (int k = iFileNum; k > i; k--)
			{
				memcpy(&m_file[k],&m_file[k-1],sizeof(struct _finddata_t));
			}
			memcpy(&m_file[i], File, sizeof(struct _finddata_t));
			iFileNum++;
			return;
		}
	}												
	memcpy(&m_file[iFileNum++], File, sizeof(struct _finddata_t));     
	return;
}
void FileIO::prinfFile(void)
{
	time_t filewrite;
	struct tm * lt = NULL;
	char buf[256];
	char mode[10];
	printf("==번호=============파일명=========================수정한 날짜============모드==\n");
	for (int i = 0; i < iFileNum; i++)
	{
		if (Binarytextload(m_file[i].name))
		{
			strcpy(mode, "Text");
		}
		else
		{
			strcpy(mode, "Binary");
		}
		filewrite = m_file[i].time_write;
		lt = localtime(&filewrite);
		strftime(buf, 256, "%y년 %m월 %d일 %H시 %M분 %S초", lt);
		printf("  %2d.%30s\t%20s\t%s\n",i+1,m_file[i].name,buf,mode);
	}
	printf("===============================================================================\n");
}
int  FileIO::Binarytextsave(void)
{
	int iSelect;
	while (1)
	{
		printf("파일 저장 형식을 고르세요.(1.Text, 2.Binary): ");
		scanf("%d", &iSelect);
		switch (iSelect)
		{
		case 1:
			return 1;
		case 2:
			return 0;
		default:
			puts("잘못된 입력입니다.");
		}
	}
}
int  FileIO::Binarytextload(char* pFilename)
{
	int i;
	for (i = 0;i < iFileNum;i++)
	{
		if (!_stricmp(pFilename, m_file[i].name))
		{
			break;
		}
	}
	FILE * fp = fopen(m_file[i].name, "r");
	int Binary;
	fscanf(fp, "%d", &Binary);
	if (Binary)
	{
		fclose(fp);
		return 1;
	}
	else
	{
		fclose(fp);
		return 0;
	}
}
char* FileIO::Datafileload(void)
{
	if (iFileNum == 0)
	{
		FindFile();
	}
	prinfFile();
	int iSelect;
	while (1)
	{
		printf("불러올 파일 번호를 선택하세요(20:취소): ");
		scanf("%d", &iSelect);
		if (iSelect <= MAXNUM && iSelect >= 0)
		{
			return m_file[iSelect - 1].name;
		}
		else if (iSelect == 20)
		{
			break;
		}
		else
		{
			puts("잘못된 입력입니다.");
		}
	}
	return NULL;
}
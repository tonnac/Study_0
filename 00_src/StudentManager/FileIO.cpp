#include "FileIO.h"

int FileIO::iFileNum = 0;

FileIO::FileIO()
{
	g_file = new _finddata_t[MaxCount];
}

FileIO::~FileIO()
{
	delete[]g_file;
}

void FileIO::FileSave(const StudentLinkedList& src)
{
	FILE * fp;
	StudentData * temp = src.getHead();
	int Binary = 0;
	time_t now = time(NULL);
	struct tm * lt = localtime(&now);
	char output[256];
	strftime(output, 256, "%y년%m월%d일%H시%M분%S초", lt);
	strcat(output, ".txt");
	fp = fopen(output, "wt");
	if (fp == NULL)
	{
		system("cls");
		puts("파일 불러오기 실패.");
		return;
	}

	fprintf(fp, "1\n");
	fprintf(fp, "%d", StudentData::m_sCounter);
	for (int iCnt = 1; iCnt < StudentData::m_sCounter; iCnt++)
	{
		fprintf(fp, "\n%d %s %d %d %d %d", temp->getNum(),
			temp->getName(),
			temp->getKor(),
			temp->getMat(),
			temp->getEng(),
			temp->getTotal()
		);
		temp = temp->m_pNext;
	}
	system("cls");
	printf("%s 파일에 저장되었습니다.\n", output);
	fclose(fp);
}
void FileIO::FileLoad(const char * pFilename, int n,StudentLinkedList* src)
{
	char Name[256];
	int Num;
	int Kor;
	int Mat;
	int Eng;
	int Total;
	int Binary;
	FILE * fp;
	fp = fopen(pFilename, "rt");
	if (fp == NULL)
	{
		system("cls");
		puts("파일 불러오기 실패.");
		return;
	}
	if (src != nullptr)
	{
		src->~StudentLinkedList();
	}
	fscanf(fp, "%d", &Binary);
	fscanf(fp, "%d", &StudentData::m_sCounter);
	for (int iCnt = 1; iCnt < StudentData::m_sCounter; iCnt++)
	{

		fscanf(fp, "\n%d %s %d %d %d %d", &Num,
			Name,
			&Kor,
			&Mat,
			&Eng,
			&Total
		);
		src->AddLink(new StudentData(Name, Kor, Mat, Eng,Num));
		StudentData::m_sCounter--;
	}
	fclose(fp);
	system("cls");
	printf("%s 파일을 불러왔습니다.\n", pFilename);
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
	if (iFileNum >= MaxCount)
	{
		return;
	}

	for (int i = 0; i < iFileNum; i++)							      // Mem to mem
	{
		memcpy(&temp, &g_file[i], sizeof(struct _finddata_t));
		if (File->time_create > temp.time_create)
		{
			for (int k = iFileNum; k > i; k--)
			{
				memcpy(&g_file[k], &g_file[k - 1], sizeof(struct _finddata_t));
			}
			memcpy(&g_file[i], File, sizeof(struct _finddata_t));
			iFileNum++;
			return;
		}
	}
	memcpy(&g_file[iFileNum++], File, sizeof(struct _finddata_t));                                //    Strc to strc       
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
		if (Binarytextload(g_file[i].name))
		{
			strcpy(mode, "Text");
		}
		else
		{
			strcpy(mode, "Binary");
		}
		filewrite = g_file[i].time_write;
		lt = localtime(&filewrite);
		strftime(buf, 256, "%y년 %m월 %d일 %H시 %M분 %S초", lt);
		printf("  %2d.%30s\t%20s\t%s\n", i + 1, g_file[i].name, buf, mode);
	}
	printf("===============================================================================\n");
}
int FileIO::Binarytextload(char* pFilename)
{
	int i;
	for (i = 0; i < iFileNum; i++)
	{
		if (!_stricmp(pFilename, g_file[i].name))
		{
			break;
		}
	}
	FILE * fp = fopen(g_file[i].name, "r");
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
		if (iSelect <= MaxCount && iSelect >= 0)
		{
			return g_file[iSelect - 1].name;
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

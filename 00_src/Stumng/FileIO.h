#pragma once
#include "Stumng.h"
#include <io.h>
#define FILE_MAX 15

struct _finddata_t g_file[MAX_COUNT];
int iFileNum = 0;

void FileSave(void);
void FileLoad(const char * pFilename, int n);
int FileCheck(const char * pFilename);
void FindFile(void);
void FileSort(struct _finddata_t * pFile);
void prinfFile(void);
int Binarytextsave(void);
int Binarytextload(char* pFilename);
char* Datafileload(void);

void FileSave (void)
{
	FILE * fp;
	int Mode;
	int Binary = 0;
	time_t now = time(NULL);
	struct tm * lt = localtime(&now);
	char output[256];
	strftime(output, 256, "%y��%m��%d��%H��%M��%S��", lt);
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
				puts("���� �ҷ����� ����.");
				return;
			}

			fprintf(fp, "1\n");
			fprintf(fp, "%d", iIndex);
			for (int iCnt = 0; iCnt < iIndex; iCnt++)
			{
				fprintf(fp, "\n%d %s %d %d %d %d %f", StudentData[iCnt].m_iNum,
					StudentData[iCnt].m_Name,
					StudentData[iCnt].m_iKor,
					StudentData[iCnt].m_iEng,
					StudentData[iCnt].m_iMat,
					StudentData[iCnt].m_iTotal,
					StudentData[iCnt].m_fAverage);
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
				puts("���� �ҷ����� ����.");
				return;
			}
			fprintf(fp, "%d",Binary);
			fwrite((void*)&iIndex, sizeof(int), 1, fp);
			fwrite((void*)StudentData, sizeof(Student), iIndex, fp);
		}
		else
		{
			return;
		}

	}
	system("cls");
	printf("%s ���Ͽ� ����Ǿ����ϴ�.\n", output);
	fclose(fp);
}
void FileLoad(const char * pFilename, int n)
{
	int Binary;
	FILE * fp;
	if (n)
	{
		fp = fopen(pFilename, "rt");
		if (fp == NULL)
		{
			system("cls");
			puts("���� �ҷ����� ����.");
			return;
		}
		fscanf(fp, "%d", &Binary);
		fscanf(fp, "%d", &iIndex);
		if (StudentData == NULL)
		{
			StudentData = (Student*)malloc(sizeof(Student)*iIndex);
		}
		for (int iCnt = 0; iCnt < iIndex; iCnt++)
		{
			fscanf(fp, "%d %s %d %d %d %d %f",
				&StudentData[iCnt].m_iNum,
				StudentData[iCnt].m_Name,
				&StudentData[iCnt].m_iKor,
				&StudentData[iCnt].m_iEng,
				&StudentData[iCnt].m_iMat,
				&StudentData[iCnt].m_iTotal,
				&StudentData[iCnt].m_fAverage);
		}
	}
	else
	{
		fp = fopen(pFilename, "rb");
		if (fp == NULL)
		{
			system("cls");
			puts("���� �ҷ����� ����.");
			return;
		}
		fscanf(fp, "%d", &Binary);
		fread((void*)&iIndex, sizeof(int), 1, fp);
		if (StudentData == NULL)
		{
			StudentData = (Student*)malloc(sizeof(Student)*iIndex);
		}
		fread((void*)StudentData, sizeof(Student), iIndex, fp);
	}
	fclose(fp);
	system("cls");
	printf("%s ������ �ҷ��Խ��ϴ�.\n", pFilename);
}
int FileCheck(const char * pFilename)
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
		printf("���Ͽ� �����Ͱ� �̹� �����մϴ�. ����ðڽ��ϱ�(Y/N): ");
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
			puts("�߸��� �Է��Դϴ�.\n\n");
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
void FindFile(void)
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
void FileSort(struct _finddata_t * File)
{
	struct _finddata_t temp;
	if (iFileNum >= FILE_MAX)
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
				memcpy(&g_file[k],&g_file[k-1],sizeof(struct _finddata_t));
			}
			memcpy(&g_file[i], File, sizeof(struct _finddata_t));
			iFileNum++;
			return;
		}
	}												
	memcpy(&g_file[iFileNum++], File, sizeof(struct _finddata_t));   // Mem to mem
	/*for (int i = 0; i < index; i++)                        //    Strc to strc
	{
		
		if (File->time_create > g_file[i].time_create)
		{
			for (int k = index; k > i; k--)
			{
				g_file[k] = g_file[k-1];
			}
			g_file[i] = *File;
			index++;
			return;
		}
	}                           
	g_file[index++] = *File;*/                               //    Strc to strc       
	return;
}
void prinfFile(void)
{
	time_t filewrite;
	struct tm * lt = NULL;
	char buf[256];
	char mode[10];
	printf("==��ȣ=============���ϸ�=========================������ ��¥============���==\n");
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
		strftime(buf, 256, "%y�� %m�� %d�� %H�� %M�� %S��", lt);
		printf("  %2d.%30s\t%20s\t%s\n",i+1,g_file[i].name,buf,mode);
	}
	printf("===============================================================================\n");
}
int Binarytextsave(void)
{
	int iSelect;
	while (1)
	{
		printf("���� ���� ������ ������.(1.Text, 2.Binary): ");
		scanf("%d", &iSelect);
		switch (iSelect)
		{
		case 1:
			return 1;
		case 2:
			return 0;
		default:
			puts("�߸��� �Է��Դϴ�.");
		}
	}
}
int Binarytextload(char* pFilename)
{
	int i;
	for (i = 0;i < iFileNum;i++)
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
char* Datafileload(void)
{
	if (iFileNum == 0)
	{
		FindFile();
	}
	prinfFile();
	int iSelect;
	while (1)
	{
		printf("�ҷ��� ���� ��ȣ�� �����ϼ���(20:���): ");
		scanf("%d", &iSelect);
		if (iSelect <= FILE_MAX && iSelect >= 0)
		{
			return g_file[iSelect - 1].name;
		}
		else if (iSelect == 20)
		{
			break;
		}
		else
		{
			puts("�߸��� �Է��Դϴ�.");
		}
	}
	return NULL;
}
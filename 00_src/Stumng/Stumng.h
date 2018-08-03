#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_COUNT 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
	char m_Name[4];
	int m_iNum;
	int m_iKor;
	int m_iEng;
	int m_iMat;
	int m_iTotal;
	float m_fAverage;
}Student;

Student * StudentData = 0;
int iIndex = 0;

enum
{
	Datainput = 1,
	Dataprint,
	DataAdd,
	DataEdit,
	Datafindname,
	Datafindindex,
	Datadelete,
	DataSave,
	DataLoad,
	Exit = 99	
};


void InputData(void);
void PrintData(void);
void Findname(char * sr);
void Findindex(int iSearch);
void DeleteData(char * sr);
void Datarenew(void);
void DataShow(int iIndex);
void ClearBuffer(void);
void AddData(void);
void EditData(void);
void StudentAdd(int n);

void Datarenew(void)
{
	for (int i = 0;i < MAX_COUNT;i++)
	{
		StudentData[i].m_Name[0] = 65 + rand() % 26;
		StudentData[i].m_Name[1] = 65 + rand() % 26;
		StudentData[i].m_Name[2] = 65 + rand() % 26;
		StudentData[i].m_Name[3] = 0;

		StudentData[i].m_iNum = (1+iIndex++);
		StudentData[i].m_iKor = rand() % 101;
		StudentData[i].m_iEng = rand() % 101;
		StudentData[i].m_iMat = rand() % 101;

		StudentData[i].m_iTotal = StudentData[i].m_iKor +
			StudentData[i].m_iEng + StudentData[i].m_iMat;

		StudentData[i].m_fAverage = StudentData[i].m_iTotal / (float)3;
	}
	puts("데이터 입력 완료\n");
}
void InputData(void)
{
	if (StudentData != NULL)
	{
		char ch;
		printf("자료를 삭제하시겠습니까(Y/N)");
		ch = getchar();
		switch (ch)
		{
		case 89:
		case 121:
		{
			iIndex = 0;
			free(StudentData);
			StudentData = NULL;
			break;
		}
		case 78:
		case 110:
		{
			system("cls");
			return;
		}
		default:
			puts("잘못된 입력입니다.");
			return;
		}
	}
	StudentData = (Student*)malloc(sizeof(Student)*MAX_COUNT);
	Datarenew();
}
void PrintData(void)
{
	printf("======================================================\n");
	printf("번호\t이름\t국어\t영어\t수학\t총점\t평균\n");
	for (int i = 0;i < iIndex;i++)
	{
		DataShow(i);
	}
	printf("======================================================\n");
}
void Findname(char * sr)
{
	for (int i = 0;i < iIndex;i++)
	{
		if (!_stricmp(sr, StudentData[i].m_Name))
		{
			printf("======================================================\n");
			printf("번호\t이름\t국어\t영어\t수학\t총점\t평균\n");
			DataShow(i);
			printf("======================================================\n");
			return;
		}
	}
	puts("\n해당하는 이름이 존재하지않습니다.\n\n");
}
void DataShow(int iIndex)
{
	printf("%3d\t", StudentData[iIndex].m_iNum);
	printf("%4s\t", StudentData[iIndex].m_Name);
	printf("%3d\t", StudentData[iIndex].m_iKor);
	printf("%3d\t", StudentData[iIndex].m_iEng);
	printf("%3d\t", StudentData[iIndex].m_iMat);
	printf("%2d\t", StudentData[iIndex].m_iTotal);
	printf("%2.2f\n", StudentData[iIndex].m_fAverage);
}
void Findindex(int iSearch)
{
	for (int i = 0;i < iIndex;i++)
	{
		if (iSearch == StudentData[i].m_iNum)
		{
			printf("======================================================\n");
			printf("번호\t이름\t국어\t영어\t수학\t총점\t평균\n");
			DataShow(i);
			printf("======================================================\n");
			return;
		}
	}
	puts("\n해당하는 번호가 존재하지않습니다.\n\n");
}
void DeleteData(char * sr)
{
	for (int i = 0;i < iIndex;i++)
	{
		if (!_stricmp(sr, StudentData[i].m_Name))
		{
			char ch;
			printf("======================================================\n");
			printf("번호\t이름\t국어\t영어\t수학\t총점\t평균\n");
			DataShow(i);
			printf("======================================================\n");
			printf("정말로 삭제하시겠습니까(Y/N)");
			ch = getchar();
			switch (ch)
			{
			case 89:
			case 121:
				for (int j = i;j < iIndex-1;j++)
				{
					StudentData[j] = StudentData[j + 1];
				}
				iIndex--;
				system("cls");
				puts("\n자료가 삭제되었습니다.\n\n");
				return;
			case 78:
			case 110:
				system("cls");
				return;
			default:
				puts("잘못된 입력입니다.\n\n");
				return;
			}
		}
	}
	puts("\n해당하는 이름이 존재하지않습니다.\n\n");
}
void ClearBuffer(void)
{
	while (getchar() != '\n');
}
void AddData(void)
{
	if (iIndex == MAX_COUNT)
	{
		system("cls");
		puts("\n\n현재 데이터가 가득 찼습니다.\n\n");
		return;
	}
	else if (iIndex)
	{
		for (int i = 0;i < MAX_COUNT;i++)
		{
			if (i + 1 != StudentData[i].m_iNum)
			{
				for (int j = MAX_COUNT - 1;j >= i;j--)
				{
					StudentData[j] = StudentData[j - 1];
				}
				printf("\n\n%d번 학생 추가\n", i + 1);
				StudentData[i].m_iNum = i + 1;
				StudentAdd(i);
				system("cls");
				puts("\n\n학생이 추가되었습니다.\n\n");
				iIndex++;
				return;
			}
		}
	}
	else
	{
		StudentData = (Student*)malloc(sizeof(Student)*MAX_COUNT);
		printf("\n\n%d번 학생 추가\n", iIndex + 1);
		StudentData[iIndex].m_iNum = iIndex + 1;
		StudentAdd(iIndex);
		system("cls");
		puts("\n\n학생이 추가되었습니다.\n\n");
		iIndex++;
		return;
	}
}
void EditData(void)
{
	int iSelect;
	printf("학생 번호입력: ");
	scanf("%d", &iSelect);
	ClearBuffer();
	for (int i = 0;i < iIndex ; i++)
	{
		if (iSelect == StudentData[i].m_iNum)
		{
			iSelect = i;
		}
	}
	StudentAdd(iSelect);
	puts("\n\n수정되었습니다.\n\n");
}
void StudentAdd(int n)
{
	char name[4];
	printf("이름 입력: ");
	scanf("%s", name);
	strcpy(StudentData[n].m_Name, name);
	printf("국어 점수 입력: ");
	scanf("%d", &StudentData[n].m_iKor);
	ClearBuffer();
	printf("영어 점수 입력: ");
	scanf("%d", &StudentData[n].m_iEng);
	ClearBuffer();
	printf("수학 점수 입력: ");
	scanf("%d", &StudentData[n].m_iMat);
	ClearBuffer();
	StudentData[n].m_iTotal = StudentData[n].m_iKor +
		StudentData[n].m_iEng + StudentData[n].m_iMat;
	StudentData[n].m_fAverage = StudentData[n].m_iTotal / (float)3;
}
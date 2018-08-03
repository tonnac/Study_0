#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <time.h>
#include <conio.h>
#include <io.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define FILE_MAX 20

#define CAT(x) printf(#x"=%d\n",x);
#define NUMBER(X,Y,Z) X##Y##Z

struct TDATA
{
	union {
		struct {
			unsigned long Zone : 28;
			unsigned long level : 4;
		};
	unsigned long a;
	};
};

struct TDATA2
{
	union {
		struct {
			unsigned char a, b, c, d;
		}s0;
		struct {
			unsigned short x, y;
		}s1;
		unsigned long a;
	}data;
};

struct TDATA3
{
	int a;
	short b;
	char c;
	char d;
	char e;
};

int a(int num1,int num2)
{
	return num1 + num2;
}

int ab(int(*fp)(int num1, int num2), int num3)
{
	int ad = 1;
	int db = 3;
	return fp(1, 3) + num3;
}

void swap(int * a, int * b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
size_t exp(int a)
{
	if (a <= 0)
	{
		return 1;
	}

	return 2 * exp(a - 1);
}
char* FindFile(void);
void Filesort(struct _finddata_t * File);

int index = 0;
struct _finddata_t g_file[FILE_MAX];

int main()
{
	////int a = 213;
	////int b = 92384;
	////swap(&a, &b);
	////CAT(a);
	////CAT(b);
	////printf("%d\n", NUMBER(100, 200, 300));
	///*int * c = (int*)malloc(sizeof(int));
	//printf("%d\n", *c);
	//memset(c, 0, sizeof(int));
	//printf("%d\n", *c);*/
	//clock_t start = clock();
	//char ch[100];
	//time_t now = time(NULL);
	//struct tm * lt = gmtime(&now);
	//printf("%s\n",ctime(&now));
	//printf("%s\n", asctime(lt));
	//strftime(ch, 100, "%y년%m월%d일", lt);
	//printf("%s\n", ch);
	//size_t E = exp(64)-1;
	//size_t K = 0;
	//printf("%llu\n", E);
	//for (size_t i = 0; i < E; i++)
	//{
	//}
	//puts("");
	//printf("%0.5f초\n", (float)(clock() - start) / CLOCKS_PER_SEC);

	ab(a, 3);


	return 0;
}

char* FindFile(void)
{
	struct _finddata_t file;
	intptr_t hFile = _findfirst("*.txt", &file);

	if (hFile == -1L)
	{
		return NULL;
	}

	do
	{
		Filesort(&file);
	} while (_findnext(hFile, &file) == 0);
	return g_file[0].name;
}

void Filesort(struct _finddata_t * File)
{
	struct _finddata_t temp;
	if (index >= FILE_MAX)
	{
		return;
	}
	
	for (int i = 0; i < index; i++)							      // Mem to mem
	{
		memcpy(&temp, &g_file[i], sizeof(struct _finddata_t));
		if (File->time_create > temp.time_create)
		{
			for (int k = index; k > i; k--)
			{
				memcpy(&g_file[k],&g_file[k-1],sizeof(struct _finddata_t));
			}
			memcpy(&g_file[i], File, sizeof(struct _finddata_t));
			index++;
			return;
		}
	}												
	memcpy(&g_file[index++], File, sizeof(struct _finddata_t));   // Mem to mem
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
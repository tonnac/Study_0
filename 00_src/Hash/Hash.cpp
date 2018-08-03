#include <iostream>
#include <ctime>
#include <cstdlib>
#define TABLE_SIZE 1000

static const char *const testCases[] = {
	"this",
	"is",
	"a",
	"test",
	"but",
	"i",
	"should",
	"use",
	"real",
	"dictonary"
};

unsigned int Hash(const char * source)
{
	unsigned int key = 0;
	while (*source)
	{
		key += *source++;
	}
	return key % TABLE_SIZE;
}

unsigned int HashCast(const char * source)
{
	unsigned int ret = reinterpret_cast<unsigned int>(source);
	unsigned int byteret1 = (ret >> 0) & 0xff;
	unsigned int byteret2 = (ret >> 8) & 0xff;
	return (byteret1+byteret2) % TABLE_SIZE;
}

struct Table
{
	const char * table[30];
	int iCount;
	void Add(const char* pData)
	{
		table[iCount++] = pData;
	}
	const char * Get(const char* pData)
	{
		if (iCount < 2) return table[0];
		for (int i = 0; i < iCount; i++)
		{
			if (!(strcmp(table[i], pData)))
			{
				return table[i];
			}
		}
		return NULL;
	}
	Table()
	{
		iCount = 0;
	}
};

int main()
{
	srand((unsigned int)time(NULL));
	char * Test[1000];
	int iNumCount1 = sizeof(Test) / sizeof(char*);
	for (int iCnt = 0; iCnt < iNumCount1; iCnt++)
	{
		Test[iCnt] = new char[3];
		Test[iCnt][0] = 65 + rand() % 26;
		Test[iCnt][1] = 65 + rand() % 26;
		Test[iCnt][2] = 0;
	}
	Table table[TABLE_SIZE];
	int iNumCount = sizeof(testCases) / sizeof(char*);
	
	//for (int i = 0; i < iNumCount; i++)
	//{
	//	const char * source = testCases[i];
	//	unsigned int iKey = HashCast(source);
	//	table[iKey].Add(source);
	//	std::cout << iKey << std::endl;
	//}

	//for (int i = 0; i < iNumCount; i++) //뺄때도 해쉬함수로
	//{
	//	const char * source = testCases[i];
	//	unsigned int iKey = HashCast(source);
	//	std::cout << table[iKey].Get(source) << std::endl;
	//}

	for (int i = 0; i < iNumCount1; i++)
	{
		const char * source = Test[i];
		unsigned int iKey = HashCast(source);
		table[iKey].Add(source);
		std::cout << iKey << std::endl;
	}

	for (int i = 0; i < iNumCount1; i++) //뺄때도 해쉬함수로
	{
		const char * source = Test[i];
		unsigned int iKey = HashCast(source);
		std::cout << table[iKey].Get(source) << std::endl;
	}

	for (int iCnt = 0; iCnt < iNumCount1; iCnt++)
	{
		delete[]Test[iCnt];
	}
	return 0;
}
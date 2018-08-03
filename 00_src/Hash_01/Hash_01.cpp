#include <iostream>

#define TABLE_SIZE 100

using HData = const char*;

int HashFunc(HData src);

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

struct Hash
{
	HData Dearr();
	bool HisEmpty();
	void AddHData(HData src);
	int m_iCount;
	HData harr[3];
	Hash() : m_iCount(0)
	{}
};

void Hash::AddHData(HData src)
{
	if (m_iCount >= 3)
	{
		std::cout << "overflow" << std::endl;
		return;
	}
	harr[m_iCount++] = src;
}

int HashFunc(HData src)
{
	int address = reinterpret_cast<int>(src);
	int op = address  & 0xff;
	int ip = (address >> 8) & 0xff;
	return (op+ip) % TABLE_SIZE;
}
bool Hash::HisEmpty()
{
	if (m_iCount <= 0)
		return true;
	else
		return false;
}
HData Hash::Dearr()
{
	HData rn = harr[m_iCount-1];
	harr[--m_iCount] = nullptr;
	return rn;
}

int main()
{
	char * Test[50];
	for (int i = 0; i < 50; i++)
	{
		Test[i] = new char[3];
		Test[i][0] = rand() % 26 + 65;
		Test[i][1] = rand() % 26 + 65;
		Test[i][2] = 0;
	}
	Hash h1[TABLE_SIZE];
	int Len = sizeof(Test) / sizeof(char*);
	for (int i = 0; i < Len; i++)
	{
		int idx = HashFunc(Test[i]);
		h1[idx].AddHData(Test[i]);
	}
	
	int a = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		while (!(h1[i].HisEmpty()))
		{
			std::cout << h1[i].Dearr() << " " << a++ << std::endl;
		}
	}

	for (int i = 0; i < 50; i++)
	{
		delete[]Test[i];
	}
	return 0;
}
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>


using namespace std;
#define MAX_NAME 20

class Student1
{
public:
	Student1(const char*_name, int _age);
	~Student1();
	void Show(void);
	static int GetCount();
	static int CompareAge(const void *a, const void *b);
	static int CompareName(const void *a, const void *b);

private:
	int age;
	char name[MAX_NAME];
	static int count;
};


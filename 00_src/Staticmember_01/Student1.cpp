#include "Student1.h"

int Student1::count = 0;

Student1::Student1(const char*_name,int _age)
{
	strncpy(this->name, _name, MAX_NAME);
	age = _age;
	count++;
}


Student1::~Student1()
{
	count--;
}

void Student1::Show()
{
	cout << name;
	cout << "(" << age << ")";
	cout << endl;
}

int Student1::GetCount()
{
	return count;
}

int Student1::CompareAge(const void*a, const void*b)
{
	Student1*pa = (Student1*)a;
	Student1*pb = (Student1*)b;
	if (pa->age > pb->age)
	{
		return 1;
	}
	else if (pa->age < pb->age)
	{
		return -1;
	}
	else return 0;
}

int Student1::CompareName(const void*a, const void*b)
{
	Student1*pa = (Student1*)a;
	Student1*pb = (Student1*)b;
	return strcmp(pa->name, pb->name);
}
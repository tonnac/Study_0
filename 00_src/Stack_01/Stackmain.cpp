#include "Stack.h"
#include "Stack.cpp"

class Student
{
public:
	int m_iID;

	Student(const int& iData)
	{
		m_iID = iData;
	}
	Student()
	{
		m_iID = -1;
	}
	bool operator == (const Student& src)
	{
		if (m_iID == src.m_iID)
		{
			return true;
		}
		return false;
	}

	bool operator == (const Student* src) //& * 오버로딩 X
	{
		if (m_iID == src->m_iID)
		{
			return true;
		}
		return false;
	}
};

void PRINT(Student* Data)
{
	std::cout << Data->m_iID << " ";
}


int main()
{
	Stack<Student*> stack;
	Student a(0), b(1), c(2), d(3);
	stack.Push(new Student(3));
	stack.Push(new Student(1));
	stack.Push(new Student(4));
	stack.Push(new Student(6));
	stack.Push(new Student(8));
	stack.Push(&a);
	stack.Push(&b);
	stack.Push(&c);
	stack.Push(&d);

	Student e(10);
	stack.Push(&e);

	int iCnt = stack.m_iTop + 1;
	for (int i = 0; i < iCnt; i++)
	{
		stack.Pop();
	}

	

	return 0;
}
#include "KQueue_Array.cpp"
#include <ctime>

class Info
{
private:
	int m_iData;
	friend ostream& operator << (ostream&os, const Info& data);
public:
	Info() : m_iData(0) {}
	Info(int m_iInfo) : m_iData(m_iInfo) {}
};

ostream& operator << (ostream&os, const Info& data)
{
	os << data.m_iData << " ";
	return os;
}

int main()
{
	//srand((unsigned int)time(NULL));
	//int data;
	//KQueue_Array<int> QA;
	//if (QA.empty())
	//{
	//	cout << "Empty" << endl;
	//}
	//for (int i = 0;i < 20;i++)
	//{
	//	QA.put(rand() % 30);
	//}
	//QA.show();
	//for (;!QA.empty();)
	//{
	//	QA.pop();
	//}

	///////////////////////////////////////////////////////////////////

	//KQueue_Array<Info> iQ;
	//Info sv;
	//Info a = 5;
	//Info b = 1;
	//Info c = 8;
	//Info d = 32;
	//Info e = 5;
	//iQ.put(a);
	//iQ.put(b);
	//iQ.put(c);
	//iQ.put(d);
	//iQ.put(e);

	//iQ.peek(sv);

	//iQ.show();

	//do
	//{
	//	iQ.pop();
	//} while (!iQ.empty());

	//if (iQ.empty())
	//{
	//	cout << "Empty" << endl;
	//}

	KQueue_Array<Info*> iqq;
	Info* sv;
	iqq.put(new Info(3));
	iqq.put(new Info(4));
	iqq.put(new Info(5));
	iqq.put(new Info(6));
	iqq.put(new Info(7));


	iqq.show();

	do
	{
		iqq.peek(sv);
		delete sv;
		iqq.pop();
	} while (!iqq.empty());

	if (iqq.empty())
	{
		cout << "Empty" << endl;
	}
	iqq.peek(sv);

	return 0;
}
#include <iostream>
#include "Stack_LinkedList.cpp"
#include "KStackList.cpp"
#include <vector>

using namespace std;

class Info
{
private:
	friend std::ostream& operator << (std::ostream&os, const Info& data);
	int m_iData;
public:
	Info() : m_iData(0) {}
	Info(int m_iInfo) : m_iData(m_iInfo) {}
};

std::ostream& operator << (std::ostream&os, const Info& data)
{
	os << data.m_iData << " ";
	return os;
}

int main()
{
	//KStackList<int> pk;
	//pk.empty();
	//pk.push(3);pk.push(4);
	//pk.push(5);pk.push(6);
	//pk.push(7);pk.push(8);
	//pk.push(9);pk.push(10);

	//pk.show();

	//pk.pop();
	//pk.peek();

	////////////////////////////////////////////////////////////////////////////////

	//KStackList<Info> ppk;
	//ppk.empty();
	//Info irr[9];
	//for (int i = 0; i < 9; i++)
	//{
	//	irr[i] = i + 1;
	//	ppk.push(irr[i]);
	//}

	//ppk.show();

	//for (int i = 0; i < 9; i++)
	//{
	//	ppk.pop();
	//}
	//ppk.empty();

	////////////////////////////////////////////////////////////////////////////////

	KStackList<Info*> ppk;
	ppk.empty();
	for (int i = 0; i < 9; i++)
	{
		ppk.push(new Info(i+1));
	}

	ppk.show();

	for (int i = 0; i < 9; i++)
	{
		ppk.pop();
	}
	ppk.empty();


	return 0;
}
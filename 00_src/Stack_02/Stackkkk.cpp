#include "Stack.cpp"
#include <iostream>

int recursion(int num)
{
	if (num <= 1)
	{
		return num;
	}
	int qwe = recursion(num / 2);
	return qwe;
}


class Info
{
private:
	int m_iData;
public:
	Info() : m_iData(0) {}
	Info(int m_iInfo) : m_iData(m_iInfo) {}
};

int main()
{/*
	Stack<int> pk;
	if (pk.empty())
	{
		std::cout << "empty" << std::endl;
	}
	pk.push(3);pk.push(5);
	pk.push(8);pk.push(9);
	pk.push(11);pk.push(13);
	pk.push(15);
	pk.show();
	int ad = pk.peek();

	int len = pk.getTop() + 1;
	for (int i = 0; i < len; i++)
	{
		pk.pop();
	}

	if (pk.empty())
	{
		std::cout << "\nempty" << std::endl;
	}*/

	recursion(1024);

//	Stack<Info> ppk;
//	if (ppk.empty())
//	{
//		std::cout << "empty" << std::endl;
//	}
//	Info irr[7];
//	for (int i = 0; i < 7; i++)
//	{
//		irr[i] = i;
//		ppk.push(irr[i]);
//	}
////	ppk.show();
//	Info ad = ppk.peek();
//
//	int len = ppk.getTop() + 1;
//	for (int i = 0; i < len; i++)
//	{
//		ppk.pop();
//	}
//
//	if (ppk.empty())
//	{
//		std::cout << "empty" << std::endl;
//	}



	//Stack<Info*> ppk;
	//if (ppk.empty())
	//{
	//	std::cout << "empty" << std::endl;
	//}
	//for (int i = 0; i < 7; i++)
	//{
	//	ppk.push(new Info(i));
	//}
	////	ppk.show();
	//Info * ad = ppk.peek();

	//int len = ppk.getTop() + 1;
	//for (int i = 0; i < len; i++)
	//{
	//	ppk.pop();
	//}

	//if (ppk.empty())
	//{
	//	std::cout << "empty" << std::endl;
	//}

	return 0;
}
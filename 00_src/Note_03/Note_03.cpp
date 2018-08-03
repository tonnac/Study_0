#include <iostream>

using namespace std;

void Div(int a, int b, int &c)
{
	if (b == 0) 
		throw false;
	if (b != 0)
	{
		c = a / b;
	}
}

int DivA(int a, int b, int &c)
{
	if (b == 0)
		return false;
	if (b != 0)
	{
		c = a / b;
		if (c < 0)
		{
			return 'A';
		}
	}
	return 3.14;
}

int main(void)
{
	int a = 10;
	int b = 0;
	int c = 0;
	// try{ throw } catch{}
	try
	{
		DivA(a, b, c);
		cout << c << endl;
	}
	catch (bool bRet)
	{
		cout << "불리언-계산오류" << endl;
	}
	catch (int iRet)
	{
		cout << "정수 계산오류" << endl;
	}
	catch (...)
	{

	}
}
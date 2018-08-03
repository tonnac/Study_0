#include <iostream>

using namespace std;

void compute(int num)
{
	if (num == 0)
		throw 0;
	else if (num > 100)
		throw 1;
	else if (num % 2 == 1)
		throw 2;
}

void print(int num)
{
	if (num < 0)
		throw 'x';
}

int main(void)
{
	int num;
	cout << "0< <100 n%2==0";
	cin >> num;
	try
	{
		compute(num);
		cout << "done" << endl;
		print(num);
		cout << "printed" << endl;
	}
	catch (int qq)
	{
		switch (qq)
		{
		case 0:
			cout << "0!" << endl;
			break;
		case 1:
			cout << "100>" << endl;
			break;
		case 2:
			cout << "1,3,5" << endl;
		}
	}
	catch (char prr)
	{
		cout << "<0 X" << endl;
	}
	return 0;
}
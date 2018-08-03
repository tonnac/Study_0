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

int main(void)
{
	int num;
	cout << "0< <100 Â¦¼ö";
	cin >> num;
	try
	{
		compute(num);
		cout << "Done" << endl;
	}
	catch (int pp)
	{
		switch (pp)
		{
		case 0:
			cout << "0!" << endl;
			break;
		case 1:
			cout << "100>!" << endl;
			break;
		case 2:
			cout << "1,3,5" << endl;
		}
	}
	return 0;
}
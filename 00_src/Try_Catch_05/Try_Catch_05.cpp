#include <iostream>

using namespace std;

void compute(int num)
{
	if (num % 2 == 1)
		throw - 1;
	else if (num > 100)
		throw - 1;
	else if (num < 0)
		throw 5;
}


int main()
{
	int num;
	cout << "input";
	cin >> num;

	try
	{
		compute(num);
		cout << "done" << endl;
	}
	catch (...)
	{
		cout << "XX" << endl;
	}
	return 0;
}
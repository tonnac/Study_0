#include <iostream>

using namespace std;

void Divide(double dividend, double divider, double &result)
{
	if (divider == 0)
		throw false;
	result = dividend / divider;
}


int main(void)
{
	double a, b, result;
	cout << "입력!";
	cin >> a;
	cin >> b;
	try
	{
		Divide(a, b, result);
		cout << a << "/" << b << "=" << result << endl;
	}
	catch (bool exception)
	{
		cout << "잘못" << endl;
	}
	return 0;
}
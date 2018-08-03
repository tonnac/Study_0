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
	cout << "�Է�!";
	cin >> a;
	cin >> b;
	try
	{
		Divide(a, b, result);
		cout << a << "/" << b << "=" << result << endl;
	}
	catch (bool exception)
	{
		cout << "�߸�" << endl;
	}
	return 0;
}
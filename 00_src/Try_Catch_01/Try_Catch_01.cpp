#include <iostream>

using namespace std;

bool Divide(double dividend, double divider, double & result)
{
	if (divider == 0)
		return false;
	result = dividend / divider;
	return true;
}

int main(void)
{
	double a, b, result;
	cout << "�Է�!";
	cin >> a;
	cin >> b;
	if (Divide(a, b, result))
	{
		cout << a << "/" << b << "=" << result << endl;
	}
	else
	{
		cout << "�Է��� �߸��ƽ��ϴ�." << endl;
	}
	return 0;
}
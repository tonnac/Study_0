#include <iostream>

using namespace std;

int main(void)
{
	const int num = 50;
	int cast = const_cast<int&>(num);
	cast = 30;
	cout << num << " " << cast << endl;
}
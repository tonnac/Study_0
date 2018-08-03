#include <iostream>

using namespace std;

void f()
{
	char ch;
	int i = 97;
	float f = 9.32;
	double dbl;

	ch = static_cast<char>(i);
	dbl = static_cast<double>(f);
	i = static_cast<char>(ch);
	cout << ch << endl;
	cout << dbl << endl;
	cout << (char)i << endl;
}
class B
{
public:
	virtual void Test() {}
};

int main(void)
{
	f();
}
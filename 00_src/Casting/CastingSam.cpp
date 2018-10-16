#include <iostream>
#include <map>
#include <windows.h>

using namespace std;

struct a
{
	a() : b(2), c(3)
	{}
	int b;
	int c;
};

int main()
{
	map<int, a> pe;
	a ee;
	pe.insert(make_pair(1, ee));

	LPVOID lll = &pe[1];

	a* qwe = (a*)lll;

	return 0;
}
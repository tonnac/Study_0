#include "TSwap.h"
#include "TSize.h"

int main()
{
	long long p = 30;
	short l = 40;
	char q = 3;
	intptr_t m = 50;
	time_t te = 40;
	size_t dsd = 30;
	unsigned int zz = 20;
	int a = 1, b = 2;
	Swap(a, b);
	cout << a << ", " << b << endl;
	double c = 0.1, d = 0.2;
	Swap(c, d);
	cout << c << ", " << d << endl;
	char * ch = "qweqwe";
	char * ke = "asdasd";
	Swap(ch, ke);
	cout << ch << "  " << ke << endl;

	Size(p);
	Size(l);
	Size(q);
	Size(m);
	Size(te);
	Size(dsd);
	Size(zz);
	Size(a);
	Size(c);
	Size(ch);
	Size(ke);


	return 0;
}
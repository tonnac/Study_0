#include "Arrayee.h"

int main()
{
	Arrayee<double>zk(10.2, 20.3, 30.5);
	Arrayee<char>ch('a', 'b', 'c');
	Arrayee<long>ld(392, 934, 1920);
	Arrayee<char*>oo("qwe", "ewq", "zxc");

	zk.Show();
	ch.Show();
	ld.Show();
	oo.Show();
	return 0;
}
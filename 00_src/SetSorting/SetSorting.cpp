#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

struct Cmp
{
	bool operator() (int* a, int * b)
	{
		return *a < *b;
	}
};

int main(void)
{
	int * ptr = new int[10];
	set<int*, Cmp> ep;
	for (int i = 0; i < 10; ++i)
	{
		ptr[i] = i + 1;
		ep.insert(&ptr[i]);

	}
	vector<int> p;
	p.push_back(5);
	p.push_back(3);
	p.push_back(7);
	ptr[4] = 30;
	ptr[6] = 0;
	ptr[7] = 99;
	sort(ep.begin(), ep.end());

	return 0;
}
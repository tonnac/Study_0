#include <iostream>
#include <string>
#include <vector>
using namespace std;

string ReplaceAll(string& src, const string & from, const string & to)
{
	string::iterator iter = src.begin();

	while (iter != src.end())
	{
		string::iterator temp = iter;
		int fromlength = from.length();
		string find;
		for (int i = 0; i < fromlength && temp!=src.end(); i++, temp++)
		{
			find += (*temp);
		}
		if (find == from)
		{
			src.replace(iter, temp, to);
			iter += fromlength;
			continue;
		}
		iter++;
	}
	return src;
}


void ptrswap(int ** ptr)
{
	int * qe = new int;
	*qe = 30;
	*ptr = qe;
}


int main()
{
//	vector<int*> p;
//	int * ptr = new int[6];
//	*ptr = 45;
//	p.push_back(new int[3]);
//	p.push_back(new int[4]);
//	p.push_back(new int[5]);
//	p.push_back(ptr);
//	p.push_back(new int[7]);
//	p.push_back(new int[8]);
//	p.push_back(new int[9]);
//	vector<int*>::iterator iter = p.begin();
////	for (iter = p.begin(); iter != p.end(); iter++)
//	cout << *(iter +3) << " " << ptr << endl;
//	cout << endl;
//	delete[] ptr;
//	cout << *(iter + 3) << " " << ptr << endl;
//	p.erase(iter+3);

	std::vector<int> pl;
	std::vector<int>::iterator iter;
	pl.clear();
	pl.empty();
	pl.push_back(1);
	iter = pl.begin();
	pl.erase(iter);
	pl.empty();

	return 0;
}
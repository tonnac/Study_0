#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

using namespace std;

int main()
{
	unordered_multimap<int, int> ump;
	vector<int> vect;
	string ss = "qwe";
	cout << ss;
	ump.insert(make_pair(1, 1));
	ump.insert(make_pair(1, 2));
	ump.insert(make_pair(1, 3));
	ump.insert(make_pair(1, 4));
	ump.insert(make_pair(1, 5));

	ump.erase(ump.find(1));

	vect.push_back(1);
	vect.push_back(1);
	vect.push_back(1);
	vect.push_back(1);
	vect.push_back(1);

	vect.erase(find(vect.begin(), vect.end(), 1));

	return 0;
}
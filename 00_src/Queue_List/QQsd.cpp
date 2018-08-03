#include "KQ_List.cpp"
#include "KQQ_List.cpp"
#include <iostream>

using namespace std;

int main()
{
	KQQ_List<int> kd;
	int data;
	kd.put(3);kd.put(5);
	kd.put(6);kd.put(8);
	kd.put(9);kd.put(10);

	kd.show();

	kd.peek(data);

	for (;!kd.empty();)
	{
		kd.pop();
	}

	return 0;
}
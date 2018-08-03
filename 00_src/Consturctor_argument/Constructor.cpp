#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
	Array data(10);
	int i, val;
	for (i = 0;i <= 10; i++)
	{
		if (!data.SetData(i, i))
		{
			cout << "Fail to set data" << endl;
		}
		if (!data.GetData(i, val))
		{
			cout << "Fail to get data" << endl;
		}
		else
		{
			cout << "Data = " << val << endl;
		}
	}
}


#include "BSTree.h"
#include <iostream>
#include <vector>

int main(void)
{
	BSTree p1;
	for (int i = 0; i < 10; i++)
	{
		try {
			p1.insert(i + 1);
		}
		catch (bool br)
		{
			if (!br)
				std::cout << "1" << std::endl;
		}
	}
	

	return 0;
}
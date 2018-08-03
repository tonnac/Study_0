#include "KNode.h"
#include "CmpClass.h"
#include "BinSearchTree.h"

int main()
{
	BinSearchTree p1;
	for (int i = 0; i < 20; i++)
	{
		CmpClass * pe = new CmpClass(rand() % 30);
		p1.AddTree(pe);
	}
	p1.PrintTree();
	//int num;
	//std::cout << "ют╥б: ";
	//std::cin >> num;
	p1.DeleteTree(1);
	return 0;
}
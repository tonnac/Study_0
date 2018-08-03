#include <iostream>
#include "BTree.h"

int main(void)
{
	Node * avlRoot = new Node;
	memset(avlRoot, 0, sizeof(Node));
	avlRoot->m_nData = 0;

	Node * pRoot = nullptr;
	for (int i = 0; i < 10; i++)
	{
		pRoot = insert(pRoot, i);
	}


	return 0;
}
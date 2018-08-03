#include "BTreeNode.h"

int main()
{
	BTreeNode * p1 = new BTreeNode(1);
	p1->InsertNode(&p1,new BTreeNode(2));
	p1->InsertNode(&p1,new BTreeNode(3));
	p1->InsertNode(&p1,new BTreeNode(4));
	p1->InsertNode(&p1,new BTreeNode(5));
	p1->InsertNode(&p1,new BTreeNode(6));
	p1->InsertNode(&p1,new BTreeNode(7));
	p1->InsertNode(&p1, new BTreeNode(8));
	p1->InsertNode(&p1, new BTreeNode(9));

	for (int i = 0; i < 9; i++)
	{
		p1->DeleteNode(&p1, i + 1);
	}

	//p1->Heightdiff();

	p1->InorderTraverse();


	return 0;
}
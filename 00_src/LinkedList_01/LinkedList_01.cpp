#include "CircularLinkedList.h"




int main()
{
	CircularLinkedList CL;
	LinkedList LL;
	for (int i = 0; i < 10; i++)
	{
		CL.AddLink(i + 1);
		LL.AddLink(i + 1);
	}
	int iStep = 9;
	Node * temp = CL.Head;
	while (temp->m_pNext != temp)
	{
		for (int i = 0; i < iStep; i++)
		{
			temp = temp->m_pNext;
		}
		temp = CL.DelLink(temp);
	}
	CL.PrintLink();
    return 0;
}
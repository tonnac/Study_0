#include "Stack.h"
#include "Queue.h"
#include "DataStructure.h"
#include "BasicFunction.cpp"


int main()
{
	DataStructure<int> * prc = new Stack<int>;
	push<int> * spush = prc->createpush();
	pop<int> * spop = prc->createpop();
	print<int> * sprint = prc->createprint();
	empty<int> * sempty = prc->createempty();

	
	(*sempty)(prc);

	for (int i = 0; i < 11; i++)
	{
		(*spush)(prc, i + 1);
	}

	(*sprint)(prc);

	while (!(*sempty)(prc))
	{
		(*spop)(prc);
	}
	
	(*sempty)(prc);

	DataStructure<int> * qrc = new Queue<int>;
	push<int> * qpush = qrc->createpush();
	pop<int> * qpop = qrc->createpop();
	print<int> * qprint = qrc->createprint();
	empty<int> * qempty = qrc->createempty();

	(*qempty)(qrc);
	for (int i = 0; i < 11; i++)
	{
		(*qpush)(qrc, i + 1);
	}
	(*qprint)(qrc);

	for (int i = 0; i < 11; i++)
	{
		(*qpop)(qrc);
	}

	(*qempty)(qrc);

	for (int i = 0; i < 3; i++)
	{
		(*qpush)(qrc, i + 1);
	}

	(*qprint)(qrc);
	(*qpop)(qrc);
	(*qprint)(qrc);
	return 0;
}
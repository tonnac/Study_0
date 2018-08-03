#include "Queue.h"
#include <queue>

int main()
{
	std::queue<int> queueList;

	Queue queue;
	queue.Put(0);
	queue.Put(1);
	queue.Put(2);
	queue.Put(3);
	queue.Put(4);

		queue.Put(5);
	queue.Get();
	queue.Put(6); //0

}
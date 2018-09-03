#include <queue>
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

struct Node
{
	int a, b;
	struct cmp
	{
		bool operator() (Node& c, Node& d)
		{
			return c.a < d.a;
		}
		bool operator() (Node * c, Node * d)
		{
			return c->a > d->a;
		}
	};
};
int main(void)
{
	std::priority_queue<Node*,std::vector<Node*>,Node::cmp> pl;
	Node* p = new Node;
	p->a = 10;
	pl.push(p);
	p = new Node;
	p->a = 5;
	pl.push(p);
	p = new Node;
	p->a = 15;
	pl.push(p);
	pl.push(p);



	while (pl.empty() == false)
	{
		std::cout << (pl.top())->a << std::endl;
		pl.pop();
	}

	return 0;
}
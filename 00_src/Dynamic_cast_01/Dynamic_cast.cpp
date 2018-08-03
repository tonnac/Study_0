#include <iostream>

using namespace std;

class A
{
private:
	char ch;
public:
	virtual void show()
	{
		cout << ch << endl;
	}
	A() : ch('A')
	{}
};

class B : public A
{
private:
	char ch;
public:
	void show()
	{
		cout << ch << endl;
	}
	B() : ch('B')
	{}
};

class C : public B
{
private:
	char ch;
public:
	void show()
	{
		cout << ch << endl;
	}
	C() : ch('C')
	{}
};

class H
{
private:
	A * p[3];
	int idx;
public:
	H() : idx(0)
	{}
	void AddA(A * de)
	{
		p[idx++] = de;
	}
	void Show()
	{
		for (int i = 0; i < idx; i++)
		{
			p[i]->show();
		}
	}
};

int main(void)
{
	H h1;
	A* a1 = new A;
	//a1->show();
	C* a2 = dynamic_cast<C*>(a1);
	//a2->show();
	B* a3 = dynamic_cast<B*>(a1);
	//a3->show();
	h1.AddA(a1);
	h1.AddA(a2);
	h1.AddA(a3);
	h1.Show();
}